#include "basemodel.h"

#include <QDebug>

void BaseItem::addValue(const QString &key, const QVariant &value)
{
    _data[key] = value;
}

QVariant BaseItem::getValue(const QString &key)
{
    return _data[key];
}

BaseModel::BaseModel(QObject *parent)
    :_status(BaseModel::Created)
{
    qRegisterMetaType<UpdateStatus>("UpdateStatus");
}

BaseModel::UpdateStatus BaseModel::status()
{
    return _status;
}

void BaseModel::setStatus(BaseModel::UpdateStatus status)
{
    if (status != _status) {
        _status = status;
        statusUpdateChange(_status);
    }
}

BaseListModel::BaseListModel(QObject *parent)
    :BaseModel(parent)
    , QAbstractListModel(parent)
{
    connect(this, &BaseListModel::statusUpdateChange, this, &BaseListModel::statusUpdateChanged);
}

int BaseListModel::rowCount(const QModelIndex &parent) const
{
    return _storage.size();
}

QHash<int, QByteArray> BaseListModel::roleNames() const
{
    return _roles;
}

QVariant BaseListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto item = _storage[index.row()];
    auto key = _roles[role];
    return item->getValue(key);
}

void BaseListModel::statusUpdateChanged(UpdateStatus status)
{
    if (status == UpdateStatus::Updated) {
        QAbstractListModel::beginResetModel();
    }else if (status == UpdateStatus::Complete) {
        QAbstractListModel::endResetModel();
    }
}

void BaseListModel::setRoleName(QHash<int, QByteArray> roles)
{
    _roles = roles;
}
