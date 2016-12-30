#include "Utils.h"

namespace irec
{
    QList<QList<double>> getImageMatrix(const QImage& image)
    {
        QList<QList<double>> parsedImage;
        for (int i = 0; i < image.width(); ++i)
        {
            parsedImage.append(QList<double>());
            for (int j = 0; j < image.height(); ++j)
                parsedImage[i].append(QColor(image.pixel(i, j)).red() == 0 ? 0 : 1);
        }

        return parsedImage;
    }
}
