#include "jsonmodel.h"
#include <QThread>
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrentRun>
#include <QUrl>

#include "worker/networkloaderworker.h"
#include "worker/fileloaderworker.h"
#include "worker/defaultjsonreader.h"

JsonListModel::JsonListModel(QObject *parent)
    :BaseListModel(parent)
{
}

void JsonListModel::load(const QString &fileName)
{
    setStatus(BaseModel::Updated);

    if (QThread::currentThread() == QCoreApplication::instance()->thread()) {
        QtConcurrent::run(this, &JsonListModel::load, fileName);
        return;
    }

    QUrl url(fileName);

    if (url.isValid()) {
        _loaderWorker.reset(new FileLoaderWorker(_data, this));
    }else {
        _loaderWorker.reset(new NetworkLoaderWorker(_data, this));
    }

    connect(_loaderWorker.data(), &AbstractLoaderWorker::complete, this, &JsonListModel::readData, Qt::DirectConnection);
    _loaderWorker->load(fileName);
}

void JsonListModel::readData()
{
    DefaultJsonListReader *reader = new DefaultJsonListReader(_storage);
    auto role = reader->read(_data);
    setRoleName(role);

    _data.clear();
    setStatus(BaseModel::Complete);
}
