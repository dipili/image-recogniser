#pragma once

#include <QObject>

namespace irec
{
    class Perceptron;

    class PerceptronNetwork : public QObject
    {
        Q_OBJECT
    public:
        explicit PerceptronNetwork(QObject *parent = 0);
        QString recognizeLetter(QList<QList<int>> sample);

    private:
        QMap<QString, Perceptron> _perceptrons;
    };
}
