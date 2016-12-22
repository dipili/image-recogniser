#include "PerceptroNetwork.h"

#include <QMap>

#include "Perceptron.h"

namespace irec
{
    PerceptronNetwork::PerceptronNetwork(QObject *parent) : QObject(parent)
    {
    }

    // TODO improve
    QString PerceptronNetwork::recognizeLetter(QList<QList<int> > sample)
    {
        foreach (QString key, _perceptrons.keys())
        {
            if (_perceptrons.value(key).recognize(sample))
                return key;
        }

        return "Unknown";
    }
}
