#ifndef GRAPH_CONTROLLER_H
#define GRAPH_CONTROLLER_H

#include "GenericPDCController.hpp"
#include "../../view/PDCView.hpp"
#include "../../model/PDCState.hpp"
#include <dto/NodeData.hpp>

/**
 * @brief Controller object to handle the graph
 *
 */
class GraphController : public GenericPDCController
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Graph Controller object
     *
     * @param model Data handle by this controller, only the node graph
     * @param view View of the node graph
     * @param stack Used to manage Do/Undo commands
     * @param parent Qt parent to manage destruction
     */
    GraphController(GraphEditor* model, GraphViewer* view, QUndoStack* stack, QObject* parent = nullptr);

    /**
     * @brief Destroy the Graph Controller object
     *
     */
    ~GraphController();

    /**
     * @brief Controller method to handle the node picker window
     *
     * @param scene_pos position of the node picker
     */
    void on_open_node_picker(const QPointF& scene_pos);

    /**
     * @brief Controller method to handle node position modification
     *
     * @param id ID of the mode moved
     * @param position new position of the node
     */
    void on_move_node(const Id& id, const QPointF& position);

    /**
     * @brief Controller method triggered when the view request to remove a node
     *
     * @param id ID of the node to be removed
     */
    void on_request_remove_node(const Id& id);

    /**
     * @brief
     *
     * @param from_node
     * @param from_port
     * @param to_node
     * @param to_port
     * @return * void
     */
    void on_request_create_edge(const Id& from_node, const Id& from_port, const Id& to_node, const Id& to_port);

    void on_request_remove_edge(const Id& id);

    void on_request_edit_properties(const Id& id);

    /**
     * @brief Method used to synchronize the view
     *
     * This method ask to the model data representation and
     * then ask to the view to update the node graph view
     */
    void sync_view_model(void);

private:
    GraphEditor* editor;
    GraphViewer* view;

signals:
    void node_position_changed(const Id& id, const QPointF& pos);
    void node_has_been_delete(const Id& id);
    void add_node_to_view(const NodeData& data);
    void ask_clear_scene(void);

    void add_edge_to_view(const EdgeData& data);
    void edge_has_been_delete(const Id& id);
};

#endif