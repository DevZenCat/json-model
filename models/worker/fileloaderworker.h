#ifndef FILELOADERWORKER_H
#define FILELOADERWORKER_H

#include "abstractworker.h"

class FileLoaderWorker : public AbstractLoaderWorker
{
    Q_OBJECT

    public:
        explicit FileLoaderWorker(QByteArray &data, QObject *parent = nullptr);

        void load(const QString &path) override;

    private:
        QByteArray &_data;
};

#endif // FILELOADERWORKER_H
