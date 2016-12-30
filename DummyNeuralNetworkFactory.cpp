#include "DummyNeuralNetworkFactory.h"

#include <QImage>

#include "NeuralNetwork.h"
#include "Letter.h"
#include "Utils.h"

namespace irec
{
    DummyNeuralNetworkFactory::DummyNeuralNetworkFactory()
    {
    }

    NeuralNetwork *DummyNeuralNetworkFactory::createInstance() const
    {
        NeuralNetwork* network = new NeuralNetwork();

        QList<Letter> letters;
        letters.append(Letter("0", "0.bmp"));
        letters.append(Letter("1", "1.bmp"));
        letters.append(Letter("2", "2.bmp"));
        letters.append(Letter("3", "3.bmp"));
        letters.append(Letter("4", "4.bmp"));
        letters.append(Letter("5", "5.bmp"));
        letters.append(Letter("6", "6.bmp"));
        letters.append(Letter("7", "7.bmp"));
        letters.append(Letter("8", "8.bmp"));
        letters.append(Letter("9", "9.bmp"));

        for (int i = 0; i < letters.length(); ++i)
        {
            QList<QList<double>> parsedImage = getImageMatrix(QImage(letters.at(i).imageFile));
            letters[i].image = parsedImage;

            network->addLetter(letters.at(i));
        }

        return network;
    }
}
