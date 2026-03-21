/**
 * @file GraphScene.cpp
 * @brief implement GraphScene class
 */

#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "GraphScene.hpp"
#include <utils/Log.hpp>

GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent)
{
    setSceneRect(-5000, -5000, 10000, 10000);
    temp_edge = nullptr;
}

void GraphScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());

    if (item)
    {
        QGraphicsScene::contextMenuEvent(event);
        return;
    }

    QMenu menu;

    QAction* addNode = menu.addAction("Add Node");
    QAction* action = menu.exec(event->screenPos());

    if (action == addNode)
    {
        Log::info("View ask to add node at [" + std::to_string(event->scenePos().x()) + "][" + std::to_string(event->scenePos().y()) + "]");
        emit request_add_node(event->scenePos());
    }

    event->accept();
}

void GraphScene::add_node_to_graph(const NodeData& data)
{
    auto node_view = new NodeView(data);

    addItem(node_view);

    node_items[data.node_id] = node_view;

    Log::debug("Add a node " + data.pretty_print + " at (" + std::to_string(data.position.x()) + ")(" + std::to_string(data.position.y()) + ") to the view ");
    Log::debug("Node pos (scene): " + std::to_string(node_view->scenePos().x()) + ", " + std::to_string(node_view->scenePos().x()));
    Log::debug("Node pos (item): " + std::to_string(node_view->pos().x()) + ", " + std::to_string(node_view->pos().x()));

    // connect here the moved function
    connect(node_view, &NodeView::node_moved, this, &GraphScene::on_node_move);
    connect(node_view, &NodeView::request_remove_node, this, &GraphScene::request_remove_node);
    connect(node_view, &NodeView::request_create_edge, this, &GraphScene::on_create_edge);
}

void GraphScene::clear_scene(void)
{
    clear();
    node_items.clear();
}

void GraphScene::update_node_view(const Id& id, const QPointF& pos)
{
    Log::debug("Receive a signal from the node " + id + " to update view");

    auto node_view = node_items[id];

    if (node_view->pos() == pos)
    {
        return;
    }

    node_view->setPos(pos);
}

void GraphScene::remove_node_to_graph(const Id& id)
{
    Log::debug("Receive a signal to remove the node " + id + " of the view");

    auto it = node_items.find(id);
    if (it != node_items.end())
    {
        auto item = it->second;

        // Remove all connections
        item->remove_connections();
        disconnect(item, nullptr, nullptr, nullptr);
        disconnect(nullptr, nullptr, item, nullptr);

        removeItem(item);
        node_items.erase(it);

        item->deleteLater();
    }
    else
    {
        Log::error("View receive a signal to remove the node " + id + " of the view but it doen not exist in the view");
    }
}

void GraphScene::on_create_edge(const Id& port_id, const Id& node_id)
{
    Log::debug("Start a new connection from " + port_id + " of node " + node_id);

    temp_edge = new EdgeView(port_id, node_id, node_items[node_id]->get_port_view_by_id(port_id));
    temp_edge->update_end_point(node_items[node_id]->get_port_view_by_id(port_id)->scenePos());

    addItem(temp_edge);
}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // Log::debug("Get an event");
    if (temp_edge != nullptr)
    {
        // Log::debug("Get an event on the edge");
        temp_edge->update_end_point(event->scenePos());
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if (temp_edge)
    {
        auto item = itemAt(event->scenePos(), QTransform());

        if (auto port = dynamic_cast<PortView*>(item))
        {
            Log::debug("Release on a port, will create a new edge");
            emit request_new_edge(temp_edge->get_node_src(),
                                  temp_edge->get_port_src(),
                                  port->get_node_id(),
                                  port->get_port_id());
        }
        else
        {
            Log::debug("Release not on a port");
        }

        temp_edge->deleteLater();
        temp_edge = nullptr;
    }
}

void GraphScene::on_stop_edge(const Id& port_id, const Id& node_id)
{
    if (temp_edge != nullptr)
    {


        //Release the edge now need to instantiate a real edge
        // emit a signal to the graph controller to ask to add
        // the edge to the graph with the input and the output
        emit request_new_edge(temp_edge->get_node_src(),
                              temp_edge->get_port_src(),
                              node_id,
                              port_id);


        temp_edge->deleteLater();

        temp_edge = nullptr;
    }
}