#pragma once

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

namespace irec
{
    struct Letter;
    class Perceptron;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

        QList<QList<int> > getImageMatrix(const QImage& image);

    private:
        void initializePerceptrons();
        QString recognizeLetter(QList<QList<int>> sample);

    private slots:
        void on_symbolComboBox_currentIndexChanged(int index);
        void on_recognisePushButton_clicked();
        void on_learnPushButton_clicked();
        void on_updateRefPushButton_clicked();

    private:
        Ui::MainWindow* _ui;

        QStatusBar* _statusBar;

        QList<Letter> _letters;
        QList<Perceptron> _perceptrons;
    };
}
