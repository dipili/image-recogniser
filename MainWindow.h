#pragma once

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

namespace irec
{
    class NeuralNetwork;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private slots:
        void on_symbolComboBox_currentIndexChanged(int index);
        void on_recognisePushButton_clicked();
        void on_learnPushButton_clicked();
        void on_updateRefPushButton_clicked();

    private:
        Ui::MainWindow* _ui;
        QStatusBar* _statusBar;

        NeuralNetwork* _neuralNetwork;
    };
}
