#include "BitmapForm.h"
#include "ui_BitmapForm.h"

namespace irec
{
    BitmapForm::BitmapForm(QWidget *parent) :
        QWidget(parent),
        _ui(new Ui::BitmapForm)
    {
        _ui->setupUi(this);
    }

    BitmapForm::~BitmapForm()
    {
        delete _ui;
    }
}
