#pragma once

#include <QObject>

namespace irec
{
    struct Letter
    {
        QString name;
        QString imageFile;

        QList<QList<int>> image;

        Letter(QString name, QString imageFile)
        {
            this->name = name;
            this->imageFile = imageFile;
        }
    };
}
