#ifndef EDGE_VIEW_H
#define EDGE_VIEW_H

#include <QObject>
#include <QPen>
#include <QGraphicsItem>
#include <QGraphicsPathItem>

#include <utils/Id.hpp>


class EdgeView : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:
    EdgeView(const Id& port_id, const Id& node_id, QGraphicsItem* start, QGraphicsItem* parent = nullptr) : port_id_src(port_id), node_id_src(node_id), QGraphicsPathItem(parent), start_point(start)
    {
        // Put edge behind nodes
        setZValue(-1);
        setPen(QPen(Qt::black, 2));
    }

    void update_end_point(const QPointF& scenePos)
    {
        end_point = scenePos;
        updatePath();
    }

    Id& get_port_src(void)
    {
        return port_id_src;
    }

    Id& get_node_src(void)
    {
        return node_id_src;
    }

signals:
    void edgeRequested(QGraphicsItem* start, QGraphicsItem* end);

private:
    void updatePath()
    {
        QPointF p1 = start_point->scenePos();
        QPointF p2 = end_point;

        QPainterPath path(p1);

        qreal dx = (p2.x() - p1.x()) * 0.5;

        path.cubicTo(p1.x() + dx, p1.y(),
                     p2.x() - dx, p2.y(),
                     p2.x(), p2.y());

        setPath(path);
    }

private:
    QGraphicsItem* start_point;
    QPointF end_point;

    Id port_id_src;
    Id node_id_src;
};


#endif