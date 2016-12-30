#pragma once

#include <QWidget>

namespace irec
{
    class ScribbleArea : public QWidget
    {
        Q_OBJECT

    public:
        ScribbleArea(QWidget* parent = nullptr);

        bool openImage(const QString& fileName);
        bool saveImage(const QString& fileName, const char* fileFormat);
        void setPenColor(const QColor& newColor);
        void setPenWidth(int newWidth);

        bool isModified() const;
        QColor penColor() const;
        int penWidth() const;

        QImage getImage() const;

    public slots:
        void clearImage();
        void print();

    protected:
        void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
        void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

    private:
        void drawLineTo(const QPoint& endPoint);
        void resizeImage(QImage* _image, const QSize& newSize);

    private:
        bool _modified;
        bool _scribbling;
        int _penWidth;
        QColor _penColor;
        QImage _image;
        QPoint _lastPoint;
    };
}
