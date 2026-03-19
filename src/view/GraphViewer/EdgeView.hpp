#ifndef EDGE_VIEW_H
#define EDGE_VIEW_H

#include <QGraphicsPathItem>


class EdgeView : public QGraphicsPathItem
{
public:
    void set_endpoints(QPointF a, QPointF b);
};


#endif