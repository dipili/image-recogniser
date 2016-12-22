#pragma once

#include <QObject>

namespace irec
{
    class Perceptron : public QObject
    {
        Q_OBJECT
    public:
        explicit Perceptron(int width, int height, int limit, QObject *parent = 0);

        void learnRight(QList<QList<int>> sample);
        void learnWrong(QList<QList<int>> sample);

        bool recognize(QList<QList<int>> sample);

    private:
        QList<QList<int>> _weights;
        int _limit;
    };
}
