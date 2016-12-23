#include "WeightsModel.h"

namespace irec
{
    WeightsModel::WeightsModel(QList<QList<int>> weights, QObject* parent)
        : QAbstractTableModel(parent), _weights(weights)
    {
    }

    QVariant WeightsModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        return QVariant();
    }

    int WeightsModel::rowCount(const QModelIndex& parent) const
    {
        return _weights.length();
    }

    int WeightsModel::columnCount(const QModelIndex& parent) const
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
