#include "NeuralNetwork.h"

#include "Letter.h"
#include "Perceptron.h"

namespace irec
{
    NeuralNetwork::NeuralNetwork(QObject *parent) : QObject(parent)
    {
    }

    void NeuralNetwork::initialize(double epoch, double rate)
    {
        foreach (Letter letter, _letters)
        {
            Perceptron perceptron(36, 36, 0.2);
            _perceptrons.append(perceptron);
        }

        for (int i = 0; i < _perceptrons.length(); ++i)
        {
            bool canFinsh = false;

            int curEpoch = 0;
            while (!canFinsh)
            {
                canFinsh = true;

                // training to recognize the right value
                if (!_perceptrons.at(i).recognize(_letters.at(i).image))
                {
                    canFinsh = false;

                    while (!_perceptrons.at(i).recognize(_letters.at(i).image))
                    {
                        _perceptrons[i].learnRight(_letters.at(i).image, rate);

                        if (++curEpoch > epoch)
                        {
                            canFinsh = true;
                            break;
                        }
                    }
                }

                // training to not recognize wrong values
                for (int j = 0; j < _perceptrons.length(); ++j)
                {
                    if (i != j)
                    {
                        bool recognized = _perceptrons.at(i).recognize(_letters.at(j).image);
                        if (recognized)
                        {
                            canFinsh = false;

                            while (_perceptrons.at(i).recognize(_letters.at(j).image))
                                _perceptrons[i].learnWrong(_letters.at(j).image, rate);
                        }
                    }
                }

                if (++curEpoch > epoch)
                    break;
            }
        }
    }

    void NeuralNetwork::addLetter(const Letter &letter)
    {
        _letters.append(letter);
    }

    QString NeuralNetwork::recognizeLetter(const QList<QList<double> > &sample)
    {
        for (int i = 0; i < _perceptrons.length(); ++i)
        {
            if (_perceptrons.at(i).recognize(sample))
                return _letters.at(i).name;
        }

        return "Unknown";
    }

    void NeuralNetwork::clear()
    {
        _perceptrons.clear();
        _letters.clear();
    }
    
    QList<Letter> NeuralNetwork::letters() const
    {
        return _letters;
    }
    
    QList<Perceptron> NeuralNetwork::perceptrons() const
    {
        return _perceptrons;
    }
}
