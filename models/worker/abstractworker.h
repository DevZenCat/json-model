#ifndef ABSTRACTWORKER_H
#define ABSTRACTWORKER_H

#include <QObject>
#include <QHash>

class AbstractReaderWorker : public QObject
{
    Q_OBJECT

    public:
        AbstractReaderWorker() = default;

        virtual QHash<int, QByteArray> read(const QByteArray &data) = 0;
};

class AbstractLoaderWorker : public QObject
{
    Q_OBJECT
    public:
        AbstractLoaderWorker() = default;

        virtual void load(const QString& path) = 0;

    Q_SIGNALS:
        void complete();
};

#endif // ABSTRACTWORKER_H
