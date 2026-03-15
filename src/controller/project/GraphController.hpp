#ifndef GRAPH_CONTROLLER_H
#define GRAPH_CONTROLLER_H

#include "GenericPDCController.hpp"
#include "../../view/PDCView.hpp"
#include "../../model/PDCState.hpp"
#include <dto/NodeData.hpp>


class GraphController : public GenericPDCController
{
    Q_OBJECT

public:
    GraphController(GraphEditor* model, GraphViewer* view, QUndoStack* stack, QObject* parent = nullptr);

    ~GraphController();

    void on_open_node_picker(const QPointF& scene_pos);

    void on_move_node(const Id& id, const QPointF& position);

    void sync_view_model(void);

private:
    GraphEditor* editor;
    GraphViewer* view;

signals:
    void node_position_changed(const Id& id, const QPointF& pos);
    void node_has_been_delete(const Id& id);
    void add_node_to_view(const NodeData& data);
    void ask_clear_scene(void);
};

#endif