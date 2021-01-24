#ifndef NETWORKLOADERWORKER_H
#define NETWORKLOADERWORKER_H

#include "abstractworker.h"
#include <QSharedPointer>

class QNetworkAccessManager;
class QNetworkReply;

class NetworkLoaderWorker : public AbstractLoaderWorker
{
    Q_OBJECT
    public:
        explicit NetworkLoaderWorker(QByteArray &data, QObject *parent = nullptr);

        void load(const QString &path) override;

    private Q_SLOTS:
        void loadFinished(QNetworkReply *reply);

    private:
        QByteArray &_data;

        QSharedPointer<QNetworkAccessManager> _manager;
};

#endif // NETWORKLOADERWORKER_H
