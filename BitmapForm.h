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

    private:
        Ui::BitmapForm *_ui;
    };
}
