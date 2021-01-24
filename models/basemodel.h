#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "worker/abstractworker.h"

class BaseItem
{
    public:
        BaseItem() = default;

        QVariant getValue(const QString &key);
        void addValue(const QString &key, const QVariant &value);

    private:
        QHash<QString, QVariant> _data;
};

class BaseModel
{
    public:
        enum UpdateStatus {
            Created,
            Updated,
            Complete
        };

        BaseModel(QObject *parent = 0);

        UpdateStatus status();

    protected:
        virtual void readData() = 0;

    protected:
        void setStatus(BaseModel::UpdateStatus status);

    protected:
        QByteArray _data;
        QSharedPointer<AbstractLoaderWorker> _loaderWorker;
        QSharedPointer<AbstractReaderWorker> _readerWorker;

    private:
        UpdateStatus _status;

    public:
        virtual void statusUpdateChange(UpdateStatus) = 0;
};

class BaseListModel : public QAbstractListModel, public BaseModel
{
    Q_OBJECT

    Q_ENUMS (UpdateStatus)
    Q_PROPERTY (UpdateStatus status READ status NOTIFY statusUpdateChange)

    public:
        BaseListModel(QObject *parent = 0);

        int rowCount(const QModelIndex &parent) const override;
        QHash<int, QByteArray> roleNames() const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    protected:
        void setRoleName(QHash<int, QByteArray> roles);

    private Q_SLOT:
        void statusUpdateChanged(UpdateStatus);

    Q_SIGNALS:
        void statusUpdateChange(UpdateStatus) override;

    protected:
        QList<QSharedPointer<BaseItem> > _storage;

    private:
        QHash<int, QByteArray> _roles;
};

#endif // BASEMODEL_H
