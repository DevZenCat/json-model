#ifndef DEFAULTJSONREADER_H
#define DEFAULTJSONREADER_H

#include "abstractworker.h"
#include "../basemodel.h"

class DefaultJsonReader : public AbstractReaderWorker
{
    public:
        DefaultJsonReader() = default;

        virtual QHash<int, QByteArray> read(const QByteArray &data) override;
};

class DefaultJsonListReader : public AbstractReaderWorker
{
    public:
        DefaultJsonListReader(QList<QSharedPointer<BaseItem> > &storage);

        virtual QHash<int, QByteArray> read(const QByteArray &data) override;

    private:
        QList<QSharedPointer<BaseItem> > &_storage;
};

#endif // DEFAULTJSONREADER_H
