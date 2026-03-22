#ifndef EDGE_VIEW_H
#define EDGE_VIEW_H

#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>

#include "AbstractEdgeView.hpp"
#include <utils/Log.hpp>

class EdgeView : public AbstractEdgeView
{
    Q_OBJECT

public:
    EdgeView(const Id& edge_id, const Id& node_id_src, const Id& port_id_src, const Id& node_id_dst, const Id& port_id_dst, QGraphicsItem* start, QGraphicsItem* end, QGraphicsItem* parent = nullptr) : edge_id(edge_id),
                                                                                                                                                                                                         end_point(end),
                                                                                                                                                                                                         node_id_dst(node_id_dst),
                                                                                                                                                                                                         port_id_dst(port_id_dst),
                                                                                                                                                                                                         AbstractEdgeView(start, node_id_src, port_id_src, parent)
    {
        // Put edge behind nodes
        setZValue(-1);
        setPen(QPen(Qt::black, 2));
        update_path();
    }

    void update_path(void)
    {
       AbstractEdgeView::update_path(start_point->scenePos(), end_point->scenePos());
    }

    Id& get_port_dst(void)
    {
        return port_id_dst;
    }

    Id& get_node_dst(void)
    {
        return node_id_dst;
    }

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
    {
        QMenu menu;

        QAction* remove_node = menu.addAction("Remove Edge");
        QAction* action = menu.exec(event->screenPos());

        if (action == remove_node)
        {
            Log::info("View ask to remove edge " + edge_id);
            emit request_remove_edge(edge_id);
        }

        event->accept();
    }

private:
    QGraphicsItem* end_point;

    Id edge_id;

    Id port_id_dst;
    Id node_id_dst;

signals:
    void request_remove_edge(const Id& id);
};


#endif