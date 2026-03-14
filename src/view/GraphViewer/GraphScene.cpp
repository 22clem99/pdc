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
}

void GraphScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
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