#pragma once

#include <QObject>

#include "Letter.h"
#include "Perceptron.h"

namespace irec
{
    class Perceptron;

    class NeuralNetwork : public QObject
    {
        Q_OBJECT
    public:
        explicit NeuralNetwork(QObject *parent = nullptr);

        void initialize(double epoch, double rate);
        void addLetter(const Letter& letter);

        QString recognizeLetter(const QList<QList<double>>& sample);

        void clear();

        QList<Letter> letters() const;
        QList<Perceptron> perceptrons() const;

    private:
        QList<Letter> _letters;
        QList<Perceptron> _perceptrons;
    };
}
