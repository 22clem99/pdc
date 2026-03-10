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