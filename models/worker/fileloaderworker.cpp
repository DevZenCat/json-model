#include "fileloaderworker.h"

#include <QFile>
#include <QDebug>

FileLoaderWorker::FileLoaderWorker(QByteArray &data, QObject *parent)
    : _data(data)
{}

void FileLoaderWorker::load(const QString &path)
{
    qDebug() << Q_FUNC_INFO;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "error load file: " << path;
        //error
    }

    _data = file.readAll();
    file.close();

    Q_EMIT complete();
}
