#include "BitmapForm.h"
#include "ui_BitmapForm.h"

#include "ScribbleArea.h"

namespace irec
{
    BitmapForm::BitmapForm(QWidget *parent) :
        QWidget(parent),
        _ui(new Ui::BitmapForm)
    {
        _ui->setupUi(this);

        _ui->scribbleArea->setFixedSize(36, 36);
        _ui->scribbleArea->setPenWidth(5);
        _ui->scribbleArea->setPenColor(Qt::black);
    }

    BitmapForm::~BitmapForm()
    {
        delete _ui;
    }

    bool BitmapForm::openImage(const QString &fileName)
    {
        return _ui->scribbleArea->openImage(fileName);
    }

    QImage BitmapForm::getImage() const
    {
        return _ui->scribbleArea->getImage();
    }

}

void irec::BitmapForm::on_pushButton_clicked()
{
    _ui->scribbleArea->clearImage();
}
