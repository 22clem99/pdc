/**
 * @file GraphScene.hpp
 * @brief Define the GraphScene widget
 */

#ifndef GRAPH_SCENE_H
#define GRAPH_SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QWidget>

#include "NodeView.hpp"
#include <utils/Id.hpp>
#include <dto/NodeData.hpp>


class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphScene(QObject* parent = nullptr);

    std::unordered_map<Id, NodeView*> node_items;

    void add_node_to_graph(const NodeData& data);

    void clear_scene(void);

    void update_node_view(const Id& id, const QPointF& pos);

    void remove_node_to_graph(const Id& id);

signals:
    void request_add_node(const QPointF& scene_pos);
    void on_node_move(const Id& id, const QPointF& position);
    void request_remove_node(const Id& id);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
};

#endif