#ifndef NODE_VIEW_H
#define NODE_VIEW_H

#include <QGraphicsObject>

class NodeItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit NodeItem(QObject* parent = nullptr);

};


#endif