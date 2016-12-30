#pragma once

#include <QObject>

namespace irec
{
    class Perceptron
    {
    public:
        explicit Perceptron(int width, int height, double limit);
        Perceptron();

        void learnRight(const QList<QList<double> > &sample, double speed);
        void learnWrong(const QList<QList<double>>& sample, double speed);

        bool recognize(const QList<QList<double>>& sample) const;

        QList<QList<double>> weights() const;

    private:
        QList<QList<double>> _weights;
        double _limit;
    };
}
