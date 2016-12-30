#pragma once

#include <QList>
#include <QImage>

namespace irec
{
    QList<QList<double>> getImageMatrix(const QImage& image);

    double rand(double fMin, double fMax);
}
