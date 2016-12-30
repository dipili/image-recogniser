#include "ScribbleArea.h"

#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#include <QPrinter>
#endif

#include "scribblearea.h"

namespace irec
{
    ScribbleArea::ScribbleArea(QWidget* parent) : QWidget(parent)
    {
        setAttribute(Qt::WA_StaticContents);
        _modified = false;
        _scribbling = false;
        _penWidth = 1;
        _penColor = Qt::blue;
    }

    bool ScribbleArea::openImage(const QString& fileName)
    {
        QImage loadedImage;
        if (!loadedImage.load(fileName))
        {
            return false;
        }

        QSize newSize = loadedImage.size().expandedTo(size());
        resizeImage(&loadedImage, newSize);
        _image = loadedImage;
        _modified = false;
        update();
        return true;
    }

    bool ScribbleArea::saveImage(const QString& fileName, const char* fileFormat)
    {
        QImage visibleImage = _image;
        resizeImage(&visibleImage, size());

        if (visibleImage.save(fileName, fileFormat))
        {
            _modified = false;
            return true;
        }
        else
        {
            return false;
        }
    }

    void ScribbleArea::setPenColor(const QColor& newColor)
    {
        _penColor = newColor;
    }

    void ScribbleArea::setPenWidth(int newWidth)
    {
        _penWidth = newWidth;
    }

    bool ScribbleArea::isModified() const
    {
        return _modified;
    }

    QColor ScribbleArea::penColor() const
    {
        return _penColor;
    }

    int ScribbleArea::penWidth() const
    {
        return _penWidth;
    }

    void ScribbleArea::clearImage()
    {
        _image.fill(qRgb(255, 255, 255));
        _modified = true;
        update();
    }

    void ScribbleArea::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            _lastPoint = event->pos();
            _scribbling = true;
        }
    }

    void ScribbleArea::mouseMoveEvent(QMouseEvent* event)
    {
        if ((event->buttons() & Qt::LeftButton) && _scribbling)
            drawLineTo(event->pos());
    }

    void ScribbleArea::mouseReleaseEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton && _scribbling)
        {
            drawLineTo(event->pos());
            _scribbling = false;
        }
    }

    void ScribbleArea::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        QRect dirtyRect = event->rect();
        painter.drawImage(dirtyRect, _image, dirtyRect);
    }

    void ScribbleArea::resizeEvent(QResizeEvent* event)
    {
        if (width() > _image.width() || height() > _image.height())
        {
            int newWidth = qMax(width()/* + 128*/, _image.width());
            int newHeight = qMax(height()/* + 128*/, _image.height());
            resizeImage(&_image, QSize(newWidth, newHeight));
            update();
        }
        QWidget::resizeEvent(event);
    }

    void ScribbleArea::drawLineTo(const QPoint& endPoint)
    {
        QPainter painter(&_image);
        painter.setPen(QPen(_penColor, _penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(_lastPoint, endPoint);
        _modified = true;

        int rad = (_penWidth / 2) + 2;
        update(QRect(_lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
        _lastPoint = endPoint;
    }

    void ScribbleArea::resizeImage(QImage* image, const QSize& newSize)
    {
        if (image->size() == newSize)
            return;

        QImage newImage(newSize, QImage::Format_RGB32);
        newImage.fill(qRgb(255, 255, 255));
        QPainter painter(&newImage);
        painter.drawImage(QPoint(0, 0), *image);
        *image = newImage;
    }

    QImage ScribbleArea::getImage() const
    {
        return _image;
    }

    void ScribbleArea::print()
    {
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
        QPrinter printer(QPrinter::HighResolution);

        QPrintDialog printDialog(&printer, this);
        if (printDialog.exec() == QDialog::Accepted)
        {
            QPainter painter(&printer);
            QRect rect = painter.viewport();
            QSize size = _image.size();
            size.scale(rect.size(), Qt::KeepAspectRatio);
            painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
            painter.setWindow(_image.rect());
            painter.drawImage(0, 0, _image);
        }
#endif // QT_NO_PRINTER
    }
}
