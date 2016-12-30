#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QColor>
#include <QDebug>
#include <QRgb>
#include <QStatusBar>

#include "BitmapForm.h"
#include "Perceptron.h"
#include "Letter.h"
#include "WeightsModel.h"
#include "NeuralNetwork.h"
#include "DummyNeuralNetworkFactory.h"
#include "Utils.h"

namespace irec
{
    MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), _ui(new Ui::MainWindow), _statusBar(nullptr), _neuralNetwork(nullptr)
    {
        _ui->setupUi(this);
        _statusBar = new QStatusBar(this);
        setStatusBar(_statusBar);

        _ui->tableView->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);

        _ui->sampleBmpForm->openImage("blank.bmp");

        DummyNeuralNetworkFactory factory;
        _neuralNetwork = factory.createInstance();
        _neuralNetwork->initialize(_ui->epochSpinBox->value(), _ui->speedSpinBox->value());

        foreach (Letter letter, _neuralNetwork->letters())
            _ui->symbolComboBox->addItem(letter.name);
    }

    MainWindow::~MainWindow()
    {
        delete _ui;
        delete _neuralNetwork;
    }

    void MainWindow::on_symbolComboBox_currentIndexChanged(int index)
    {
        _ui->protoBmpForm->openImage(_neuralNetwork->letters().at(index).imageFile);
        _ui->tableView->setModel(new WeightsModel(_neuralNetwork->perceptrons().at(index).weights()));
        _ui->tableView->resizeColumnsToContents();
    }

    void MainWindow::on_recognisePushButton_clicked()
    {
        QString letter = _neuralNetwork->recognizeLetter(getImageMatrix(_ui->sampleBmpForm->getImage()));
        _statusBar->showMessage(QString("The symbol is %1").arg(letter), 5000);
    }

    void MainWindow::on_learnPushButton_clicked()
    {
        _neuralNetwork->clear();
        _neuralNetwork->initialize(_ui->epochSpinBox->value(), _ui->speedSpinBox->value());
    }

    void MainWindow::on_updateRefPushButton_clicked()
    {
        _ui->protoBmpForm->getImage().save(_neuralNetwork->letters().at(_ui->symbolComboBox->currentIndex()).imageFile);

        _neuralNetwork->clear();
        _neuralNetwork->initialize(_ui->epochSpinBox->value(), _ui->speedSpinBox->value());

        _ui->tableView->setModel(new WeightsModel(_neuralNetwork->perceptrons().at(_ui->symbolComboBox->currentIndex()).weights()));
    }
}
