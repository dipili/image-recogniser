#include "Perceptron.h"

namespace irec
{
    Perceptron::Perceptron(int width, int height, int limit, QObject *parent) : QObject(parent), _limit(limit)
    {
        for (int i = 0; i < width; i++)
        {
            _weights.append(QList<int>());
            for (int j = 0; j < height; j++)
                _weights[i].append(0);
        }
    }

    void Perceptron::learnRight(QList<QList<int>> sample)
    {
        for (int i = 0; i < sample.length(); i++)
        {
            for (int j = 0; j < sample.at(0).length(); j++)
                _weights[i][j] += sample[i][j];
        }
    }

    void Perceptron::learnWrong(QList<QList<int>> sample)
    {
        for (int i = 0; i < sample.length(); i++)
        {
            for (int j = 0; j < sample.at(0).length(); j++)
                _weights[i][j] -= sample[i][j];
        }
    }

    bool Perceptron::recognize(QList<QList<int>> sample)
    {
        int sum = 0;

        for (int i = 0; i < sample.length(); i++)
        {
            for (int j = 0; j < sample.at(0).length(); j++)
                sum += sample[i][j] * _weights[i][j];
        }

        return sum >= _limit;
    }
}
