/**
 * @file GraphScene.hpp
 * @brief Define the GraphScene widget
 */

#ifndef GRAPH_SCENE_H
#define GRAPH_SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QWidget>


class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphScene(QObject* parent = nullptr);

signals:
    void request_add_node(QPointF scene_pos);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
};

#endif