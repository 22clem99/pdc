#ifndef TEMP_EDGE_VIEW_H
#define TEMP_EDGE_VIEW_H

#include "AbstractEdgeView.hpp"

class TempEdgeView : public AbstractEdgeView
{
    Q_OBJECT

public:
    TempEdgeView(const Id& port_id, const Id& node_id, QGraphicsItem* start, QGraphicsItem* parent = nullptr) : AbstractEdgeView(start, node_id, port_id, parent)
    {
        // Put edge behind nodes
        setZValue(-1);
        setPen(QPen(Qt::black, 2));
    }

    void update_end_point(const QPointF& scenePos)
    {
        end_point = scenePos;
        update_path();
    }

private:
    void update_path()
    {
        AbstractEdgeView::update_path(start_point->scenePos(), end_point);
    }

    QPointF end_point;
};


#endif