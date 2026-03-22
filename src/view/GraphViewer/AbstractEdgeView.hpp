#ifndef ABSTRACT_EDGE_VIEW_H
#define ABSTRACT_EDGE_VIEW_H

#include <QObject>
#include <QPen>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPainterPathStroker>

#include <utils/Id.hpp>


class AbstractEdgeView : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:
    AbstractEdgeView(QGraphicsItem* start_point, const Id& node_id_src, const Id& port_id_src, QGraphicsItem* parent = nullptr) : start_point(start_point), port_id_src(port_id_src), node_id_src(node_id_src), QGraphicsPathItem(parent)
    { }

    Id& get_port_src(void)
    {
        return port_id_src;
    }

    Id& get_node_src(void)
    {
        return node_id_src;
    }

    QPainterPath shape() const
    {
        QPainterPathStroker stroker;
        stroker.setWidth(10);

        return stroker.createStroke(path());
    }

protected:
    void update_path(QPointF p1, QPointF p2)
    {
        QPainterPath path(p1);

        qreal dy = (p2.y() - p1.y()) * 0.5;

        path.cubicTo(p1.x(), p1.y() + dy,
                     p2.x(), p2.y() - dy,
                     p2.x(), p2.y());

        setPath(path);
    }

    QGraphicsItem* start_point;
    // QPointF end_point;

    Id port_id_src;
    Id node_id_src;
};

#endif