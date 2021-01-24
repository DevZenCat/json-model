#include "networkloaderworker.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

NetworkLoaderWorker::NetworkLoaderWorker(QByteArray &data, QObject *parent)
    : _data(data)
{}

void NetworkLoaderWorker::load(const QString &path)
{
    QNetworkRequest request(path);
    _manager.reset(new QNetworkAccessManager);

    connect(_manager.data(), &QNetworkAccessManager::finished, this, &NetworkLoaderWorker::loadFinished);

    _manager->get(request);
}

void NetworkLoaderWorker::loadFinished(QNetworkReply *reply)
{
    if (reply->error()) {
        //Error
        return;
    }

    _data = reply->readAll();

    Q_EMIT complete();
}
