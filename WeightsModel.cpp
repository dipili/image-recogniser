#include "WeightsModel.h"

namespace irec
{
    WeightsModel::WeightsModel(QList<QList<double>> weights, QObject* parent)
        : QAbstractTableModel(parent), _weights(weights)
    {
    }

    int WeightsModel::rowCount(const QModelIndex&) const
    {
        return _weights.length();
    }

    int WeightsModel::columnCount(const QModelIndex&) const
    {
        return _weights.at(0).length();
    }

    QVariant WeightsModel::data(const QModelIndex& index, int role) const
    {
        if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole)
            return QVariant(_weights.at(index.row()).at(index.column()));

        return QVariant();
    }
}
