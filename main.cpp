#include <QCoreApplication>

#include "models/jsonmodel.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << Q_FUNC_INFO;

    JsonListModel *model = new JsonListModel(0);
    model->load("C:/listData.json");

    return a.exec();
}
