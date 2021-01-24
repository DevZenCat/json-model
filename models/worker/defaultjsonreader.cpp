#include "defaultjsonreader.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QThread>
#include "../basemodel.h"

QHash<int, QByteArray> DefaultJsonReader::read(const QByteArray &data)
{
    const auto document = QJsonDocument::fromJson(data);
    QJsonObject object = document.object();

    qDebug() << Q_FUNC_INFO << object.count() << object.keys();

    for(const auto key : object.keys())
    {
        qDebug() << Q_FUNC_INFO << key;
    }

    return QHash<int, QByteArray>();
}

DefaultJsonListReader::DefaultJsonListReader(QList<QSharedPointer<BaseItem> > &storage)
    :_storage(storage)
{}

QHash<int, QByteArray> DefaultJsonListReader::read(const QByteArray &data)
{
    const auto document = QJsonDocument::fromJson(data);
    QJsonObject object = document.object();

    QJsonArray arrayData = object["data"].toArray();

    QHash<int, QByteArray> result;

    for(const auto item : arrayData)
    {
        const auto objectItem = item.toObject();

        const auto dataItem = QSharedPointer<BaseItem>::create();

        int index = 0;
        for(const auto key : objectItem.keys())
        {
            dataItem->addValue(key, objectItem[key].toVariant());
            result[index++] = key.toUtf8();
        }

        _storage.append(dataItem);
    }

    return result;
}
