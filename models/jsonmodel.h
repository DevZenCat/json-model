#ifndef JSONMODEL_H
#define JSONMODEL_H

#include "basemodel.h"

class JsonListModel : public BaseListModel
{
    Q_OBJECT
    Q_ENUMS (UpdateStatus)

    public:
        JsonListModel(QObject *parent = 0);

        Q_INVOKABLE void load(const QString &fileName);

    private:
        void readData() override;
};

#endif // JSONMODEL_H
