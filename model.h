#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>


class MyModelList: public QAbstractListModel
{

int rowCount(const QModelIndex &parent = QModelIndex()) const override
{
    return 3;
}


};

#endif // MODEL_H
