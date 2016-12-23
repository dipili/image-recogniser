#include "Perceptron.h"

namespace irec
{
    Perceptron::Perceptron(int width, int height, int limit) : _limit(limit)
    {
        for (int i = 0; i < width; i++)
        {
            _weights.append(QList<int>());
            for (int j = 0; j < height; j++)
                _weights[i].append(0);
        }
    }

    Perceptron::Perceptron()
    {
    }

    void Perceptron::learnRight(const QList<QList<int>>& sample, double speed)
    {
        for (int i = 0; i < sample.length(); i++)
        {
            for (int j = 0; j < sample.at(0).length(); j++)
                _weights[i][j] += sample[i][j] * speed;
        }
    }

    void Perceptron::learnWrong(const QList<QList<int>>& sample, double speed)
    {
        for (int i = 0; i < sample.length(); i++)
        {
            for (int j = 0; j < sample.at(0).length(); j++)
                _weights[i][j] -= sample[i][j] * speed;
        }
    }

    bool Perceptron::recognize(const QList<QList<int>>& sample) const
    {
        int sum = 0;

        for (int i = 0; i < sample.length(); i++)
        {
            int jEnds = sample.at(i).length();
            for (int j = 0; j < jEnds; j++)
                sum += sample[i][j] * _weights[i][j];
        }

        return sum >= _limit;
    }

    QList<QList<int> > Perceptron::weights() const
    {
        return _weights;
    }
}
