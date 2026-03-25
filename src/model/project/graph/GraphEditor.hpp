/**
 * @file GraphEditor.hpp
 * @brief The object is a high level manipulation graph manipulator
 *
 * The goal of this class is to simplify graph handling
 */

#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include <QPointF>
#include <QObject>

#include "Graph.hpp"
#include <utils/Types.hpp>
#include <utils/JSONPrintable.hpp>
#include <dto/NodeData.hpp>
#include <dto/EdgeData.hpp>
#include "../node/NodeAllocator.hpp"
#include "Snapshot.hpp"


/**
 * @brief This class
 *
 */
class GraphEditor : public QObject
{
    Q_OBJECT

private:
    Graph node_graph;

public:
    /**
     * @brief Construct a new Graph Editor object
     *
     */
    GraphEditor();

    /**
     * @brief Construct a new Graph Editor object based on a JSON file
     *
     * @param j JSON content file
     */
    GraphEditor(const nlohmann::json& j);

    /**
     * @brief Destroy the Graph Editor object
     *
     * Mainly used to disconnect Qt signals
     */
    ~GraphEditor();

    /**
     * @brief Function to look if a node can be allocate
     *
     * @param node_type type of the node to be allocate
     * @return NodeCreationTestStatus status of the creation test define by DTO
     */
    NodeCreationTestStatus can_add_node(const std::string& node_type);

    /**
     * @brief Function to instantiate a node of a specific type
     *
     * @param node_type type of the node to be allocate
     * @param pos possition of the new node
     * @return NodeData data of the node, in order to be display define by DTO
     */
    NodeData add_node(const std::string& node_type, const QPointF& pos);

    /**
     * @brief Function to instantiate a node of a specific type based on a snapshot
     *
     * @param node_type type of the node to be allocate
     * @param pos possition of the new node
     * @param snapshot snapshot of the node to recreate the node
     * @return NodeData data of the node, in order to be display define by DTO
     */
    NodeData add_node_snapshot(const NodeSnapshot& snapshot);

    /**
     * @brief Function to remove a specific node
     *
     * @param node_id ID of the node to be remove
     * @return true if the node has been successfully removed
     * @return false if the node can't be removed
     */
    bool remove_node(const Id& node_id);

    /**
     * @brief Set the node possition in the model, it is used when a project is saved
     *
     * @param id node to be updated
     * @param position new possition of the node
     */
    void set_node_position(const Id& id, const QPointF& position);

    /**
     * @brief Get the node position object
     *
     * @param id node to get the possition from
     * @return QPointF possition
     */
    QPointF get_node_position(const Id& id);

    /**
     * @brief Get all nodes data object
     *
     * @return std::vector<NodeData> DTO representation of all nodes
     */
    std::vector<NodeData> get_nodes_data(void);

    /**
     * @brief Get the node type
     *
     * @param id node to get the type from
     * @return std::string type of the node, this data come from the node allocator
     */
    std::string get_node_type(const Id& id);

    /**
     * @brief Test if an edge can be add to the graph
     *
     * @param from_node node ID source of the edge
     * @param from_port port ID source of the edge
     * @param to_node node ID destination of the edge
     * @param to_port port ID destination of the edge
     * @return EdgeCreationTestStatus status of the creation edge test define by DTO
     */
    EdgeCreationTestStatus can_add_edge(const Id& from_node, const Id& from_port, const Id& to_node, const Id& to_port);

    /**
     * @brief Add an edge to the graph
     *
     * @param from_node node ID source of the edge
     * @param from_port port ID source of the edge
     * @param to_node node ID destination of the edge
     * @param to_port port ID destination of the edge
     * @return EdgeData data of the edge, in order to be display define by DTO
     */
    EdgeData add_edge(const Id& from_node, const Id& from_port, const Id& to_node, const Id& to_port, const Id& existing_id = nullid);

    EdgeData add_edge_snapshot(const EdgeSnapshot& snap);

    /**
     * @brief Remove an edge by ID
     *
     * @param edge_id ID of the edge to be removed
     * @return true edge has been successfully removed
     * @return false can't allocate the edge
     */
    bool remove_edge(const Id& edge_id);

    /**
     * @brief Get all edges data object
     *
     * @return std::vector<EdgeData> representation of all edges define by DTO
     */
    std::vector<EdgeData> get_edges_data(void);

    /**
     * @brief Get the edge data of a specific edge
     *
     * @param id ID of the edge to get data from
     * @return EdgeData edge representation defined by DTO
     */
    EdgeData get_edge_data(const Id& id);

    /**
     * @brief Get edges data for a specific node
     *
     * @param id node ID to get edge data from
     * @return std::vector<EdgeData>
     */
    std::vector<EdgeData> get_edges_data_by_node(const Id& id);

    /**
     * @brief Test if a specific port is an input
     *
     * @param node_id node from which the port is from
     * @param port_id port to be tested
     * @return true the port is an input
     * @return false the port is not an input
     */
    bool is_input(const Id& node_id, const Id& port_id);

    /**
     * @brief Test if a specific port is an output
     *
     * @param node_id node from which the port is from
     * @param port_id port to be tested
     * @return true the port is an input
     * @return false the port is not an input
     */
    bool is_output(const Id& node_id, const Id& port_id);

    /**
     * @brief Get the string representation of the GraphEditor
     *
     * @return std::string GraphEditor representation
     */
    std::string get_str(void);

    /**
     * @brief Same as get_str(void) but with tab at each lines
     *
     * @param tab number of tab to insert
     * @return std::string GraphEditor representation
     */
    std::string get_str(const unsigned int tab);

    /**
     * @brief This method is used to construct recursively a JSON project representation
     *
     * @return nlohmann::json
     */
    nlohmann::json to_json(void);

    /**
     * @brief Get a node snapshot
     *
     * @param id node to get the snapshot from
     * @return NodeSnapshot return a representation used to recreate node in case of redo/undo
     */
    NodeSnapshot get_node_snapshot(const Id& id);

    /**
     * @brief Get an edge snapshot
     *
     * @param id edge to get the snapshot from
     * @return EdgeSnapshot return a representation used to recreate edge in case of redo/undo
     */
    EdgeSnapshot get_edge_snapshot(const Id& id);

    /**
     * @brief Get the edges snapshot linked to node object
     *
     * @param id id of the node
     * @return std::vector<EdgeSnapshot>
     */
    std::vector<EdgeSnapshot> get_edges_snapshot_linked_to_node(const Id& id);

signals:
    /**
     * @brief Signal to aware the controller that a node has been added to the model
     *
     * @param data representation of the node added defined by DTO
     */
    void node_has_been_added(const NodeData& data);

    /**
     * @brief Signal to aware the controller that a node position has been changed
     *
     * @param id node to be update the view
     * @param pos new possition of the node
     */
    void node_position_changed(const Id& id, const QPointF& pos);

    /**
     * @brief Signal to aware the controller that a node has been remove
     *
     * @param id ID of the node removed
     */
    void node_has_been_delete(const Id& id);

    /**
     * @brief Signal to aware the controller that an edge has been added to the model
     *
     * @param data representation of the edge added defined by DTO
     */
    void edge_has_been_added(const EdgeData& data);

    /**
     * @brief Signal to aware the controller that an edge has been removed from the model
     *
     * @param id ID of the edge removed
     */
    void edge_has_been_delete(const Id& id);


};

#endif