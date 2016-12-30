#include "Perceptron.h"

#include "qmath.h"

namespace irec
{
    double rand(double fMin, double fMax)
    {
        double f = (double)random() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    Perceptron::Perceptron(int width, int height, double limit) : _limit(limit)
    {
        for (int i = 0; i < width; i++)
        {
            _weights.append(QList<double>());
            for (int j = 0; j < height; j++)
                _weights[i].append(rand(-0.1, 0.1));
        }
    }

    Perceptron::Perceptron()
    {
    }

    void Perceptron::learnRight(const QList<QList<double>>& sample, double speed)
    {
        for (int i = 0; i < sample.length(); i++)
        {
            for (int j = 0; j < sample.at(0).length(); j++)
            {
                _weights[i][j] += sample[i][j] * speed;
            }
        }
    }

    void Perceptron::learnWrong(const QList<QList<double> > &sample, double speed)
    {
        for (int i = 0; i < sample.length(); i++)
        {
            for (int j = 0; j < sample.at(0).length(); j++)
                _weights[i][j] -= sample[i][j] * speed;
        }
    }

    bool Perceptron::recognize(const QList<QList<double>>& sample) const
    {
        int sum = 0;

        for (int i = 0; i < sample.length(); i++)
        {
            for (int j = 0; j < sample.at(i).length(); j++)
                sum += sample[i][j] * _weights[i][j];
        }

        return sum >= _limit;
    }

    QList<QList<double> > Perceptron::weights() const
    {
        return _weights;
    }
}
