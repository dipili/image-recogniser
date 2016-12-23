#pragma once

#include <QObject>

namespace irec
{
    class Perceptron
    {
    public:
        explicit Perceptron(int width, int height, int limit);
        Perceptron();

        void learnRight(const QList<QList<int>>& sample, double speed);
        void learnWrong(const QList<QList<int>>& sample, double speed);

        bool recognize(const QList<QList<int>>& sample) const;

        QList<QList<int>> weights() const;

    private:
        QList<QList<int>> _weights;
        int _limit;
    };
}
