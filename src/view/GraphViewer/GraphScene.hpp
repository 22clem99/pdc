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
#include "EdgeView.hpp"
#include <utils/Id.hpp>
#include <dto/NodeData.hpp>


class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphScene(QObject* parent = nullptr);

    std::unordered_map<Id, NodeView*> node_items;
    std::unordered_map<Id, EdgeView*> edge_items;

    EdgeView* temp_edge;

    void add_node_to_graph(const NodeData& data);

    void clear_scene(void);

    void update_node_view(const Id& id, const QPointF& pos);

    void remove_node_to_graph(const Id& id);

    void on_create_edge(const Id& port_id, const Id& node_id);

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void on_stop_edge(const Id& port_id, const Id& node_id);

signals:
    void request_add_node(const QPointF& scene_pos);
    void on_node_move(const Id& id, const QPointF& position);
    void request_remove_node(const Id& id);
    void request_new_edge(const Id& from_port, const Id& from_node, const Id& to_port, const Id& to_node);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
};

#endif