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
    GraphController(PDCState* model, PDCView* view, QUndoStack* stack);

    ~GraphController();

    void on_open_node_picker(const QPointF& scene_pos);

    void on_move_node(const Id& id, const QPointF& position);

signals:
    void node_position_changed(const Id& id, const QPointF& pos);
    void add_node_to_view(const NodeData& data);
    void ask_clear_scene(void);
};

#endif