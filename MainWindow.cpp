#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QColor>
#include <QDebug>
#include <QRgb>
#include <QStatusBar>

#include "BitmapForm.h"
#include "Ciphering/Perceptron.h"
#include "Letter.h"
#include "WeightsModel.h"

namespace irec
{
    QList<QList<int>> MainWindow::getImageMatrix(const QImage& image)
    {
        QList<QList<int>> parsedImage;
        for (int i = 0; i < image.width(); ++i)
        {
            parsedImage.append(QList<int>());
            for (int j = 0; j < image.height(); ++j)
                parsedImage[i].append(QColor(image.pixel(i, j)).red() == 0 ? 0 : 1);
        }

        return parsedImage;
    }

    void MainWindow::initializePerceptrons()
    {
        _statusBar->showMessage("Learning...");

        foreach (Letter letter, _letters)
        {
            Perceptron perceptron(36, 36, 9);
            _perceptrons.append(perceptron);
        }

        for (int i = 0; i < _perceptrons.length(); ++i)
        {
            bool canFinsh = false;

            int curEpoch = 0;
            while (!canFinsh)
            {
                canFinsh = true;

                {
                    bool recognized = _perceptrons.at(i).recognize(_letters.at(i).image);
                    if (!recognized)
                    {
                        canFinsh = false;

                        while (!_perceptrons.at(i).recognize(_letters.at(i).image))
                        {
                            _perceptrons[i].learnRight(_letters.at(i).image, _ui->speedSpinBox->value());

                            if (++curEpoch > _ui->epochSpinBox->value())
                            {
                                canFinsh = true;
                                break;
                            }
                        }
                    }
                }

                for (int j = 0; j < _perceptrons.length(); ++j)
                {
                    if (i != j)
                    {
                        bool recognized = _perceptrons.at(i).recognize(_letters.at(j).image);
                        if (recognized)
                        {
                            canFinsh = false;

                            while (_perceptrons.at(i).recognize(_letters.at(j).image))
                                _perceptrons[i].learnWrong(_letters.at(j).image, _ui->speedSpinBox->value());
                        }
                    }
                }

                if (++curEpoch > _ui->epochSpinBox->value())
                    break;
            }
        }

        _statusBar->showMessage("Learning finished.");
    }

    MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), _ui(new Ui::MainWindow)
    {
        _ui->setupUi(this);
        _statusBar = new QStatusBar(this);
        setStatusBar(_statusBar);

        _ui->tableView->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);

        _ui->sampleBmpForm->openImage("blank.bmp");

        _letters.append(Letter("0", "0.bmp"));
        _letters.append(Letter("1", "1.bmp"));
        _letters.append(Letter("2", "2.bmp"));
        _letters.append(Letter("3", "3.bmp"));
        _letters.append(Letter("4", "4.bmp"));
        _letters.append(Letter("5", "5.bmp"));
        _letters.append(Letter("6", "6.bmp"));
        _letters.append(Letter("7", "7.bmp"));
        _letters.append(Letter("8", "8.bmp"));
        _letters.append(Letter("9", "9.bmp"));

        for (int l = 0; l < _letters.length(); ++l)
        {
            QList<QList<int>> parsedImage = getImageMatrix(QImage(_letters.at(l).imageFile));
            _letters[l].image = parsedImage;
        }

        initializePerceptrons();

        foreach (Letter letter, _letters)
            _ui->symbolComboBox->addItem(letter.name);
    }

    MainWindow::~MainWindow()
    {
        delete _ui;
    }

    QString MainWindow::recognizeLetter(QList<QList<int>> sample)
    {
        for (int i = 0; i < _perceptrons.length(); ++i)
        {
            if (_perceptrons.at(i).recognize(sample))
                return _letters.at(i).name;
        }

        return "Unknown";
    }
}

void irec::MainWindow::on_symbolComboBox_currentIndexChanged(int index)
{
    _ui->protoBmpForm->openImage(_letters.at(index).imageFile);
    _ui->tableView->setModel(new WeightsModel(_perceptrons.at(index).weights()));
    _ui->tableView->resizeColumnsToContents();
}

void irec::MainWindow::on_recognisePushButton_clicked()
{
    QString letter = recognizeLetter(getImageMatrix(_ui->sampleBmpForm->getImage()));
    _statusBar->showMessage(QString("The symbol is %1").arg(letter), 5000);
}

void irec::MainWindow::on_learnPushButton_clicked()
{
    _perceptrons.clear();
    initializePerceptrons();
}

void irec::MainWindow::on_updateRefPushButton_clicked()
{
    _ui->protoBmpForm->getImage().save(_letters.at(_ui->symbolComboBox->currentIndex()).imageFile);

    _perceptrons.clear();
    initializePerceptrons();
}
