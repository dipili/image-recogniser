#pragma once

#include <QWidget>

namespace Ui {
class BitmapForm;
}

namespace irec
{
    class BitmapForm : public QWidget
    {
        Q_OBJECT

    public:
        explicit BitmapForm(QWidget *parent = 0);
        ~BitmapForm();

        bool openImage(const QString &fileName);
        QImage getImage() const;

    private slots:
        void on_pushButton_clicked();

    private:
        Ui::BitmapForm *_ui;
    };
}
