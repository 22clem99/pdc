/**
 * @file Graph.hpp
 * @brief header for the low level graph object
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <map>
#include <memory>
#include <QObject>

#include <utils/Types.hpp>
#include "../node/Node.hpp"
#include "../edge/Edge.hpp"
#include <utils/JSONPrintable.hpp>
#include <dto/NodeData.hpp>
#include <dto/EdgeData.hpp>

/**
 * @brief Provide the result abstraction result of the graph analyze
 *
 */
class GraphAnalyzer
{
public:
    bool has_cycle;
    bool is_connected;
    bool tail_reachable;

    bool analysis_dirty = true;

    GraphAnalyzer() = default;
};

/**
 * @brief Graph object, represent nodes and edges.
 * This graph have specific properties:
 * - oriented
 * - single-entry single-exit graph (named head and tail)
 * - acyclic
 */
class Graph : public QObject
{
    Q_OBJECT
private:
    GraphAnalyzer analysis;
public:
    /**
     * @brief Map of nodes
     */
    std::map<Id, std::unique_ptr<Node>> nodes;

    /**
     * @brief Map of edges between nodes
     */
    std::map<Id, std::unique_ptr<Edge>> edges;

    std::optional<Id> head_id;
    std::optional<Id> tail_id;

    Graph() = default;
    Graph(const nlohmann::json& j);

    /**
     *  Nodes manipulation
     */

    /**
     * @brief Allocate a node and store it in the graph
     *
     * @param node_type node name to allocate, it will be used by the factory
     * @return Id generate for this new Node
     */
    Id add_node(const std::string& node_type, const QPointF& pos);

    NodeCreationTestStatus can_add_node(const std::string& node_type);

    /**
     * @brief remove the node and edges bind to it
     *
     * @param node_id node Id to be removed
     * @return true if the node is successfully removed
     * @return false if the node was not remove
     */
    bool remove_node(const Id& node_id);

    /**
     * @brief test if the node exist
     *
     * @param node_id node Id to be tested
     * @return true if the node with this ID exist in the graph
     * @return false if the node with this ID doesn't exist
     */
    bool has_node(const Id& node_id);

    /**
    * @brief test if the node has a port
    * @param node_id node Id to be tested
    * @param port_id port Id to be tested
    * @return true if the port exist otherwise false
    */
    bool has_port(const Id& node_id, const Id& port_id);

    /**
    * @brief test if the node has a port
    * @param node_id node Id to be tested
    * @param port_id port Id to be tested
    * @return true if the port exist otherwise false
    */
    bool has_edge(const Id& edge_id);

    /**
     * Edges manipulation
     */

    /**
     * @brief connect two nodes with an edge
     *
     * @param from_node edge start node
     * @param from_output output from the start node
     * @param to_node edge end node
     * @param to_input input from the end node
     * @return Id of the new edge create, if the edge can't be create, for any reason, return nullid
     */
    Id connect(const Id& from_node, const Id& from_output, const Id& to_node, const Id& to_input);

    /**
     * @brief remove an edge by ID, it will also remove reference in the node
     *
     * @param edge edge ID to be removed
     * @return true if the edge is successfully removed
     * @return false if the edge is not successfully removed
     */
    bool disconnect(const Id& edge_id);

    EdgeCreationTestStatus can_connect(const Id& from_node, const Id& from_output, const Id& to_node, const Id& to_input);

    /**
     * @brief Remove all edges connected to a node
     *
     * @param node_id node ID to clear edges
     * @return int number of edges removed
     */
    int remove_edges_of_node(const Id& node_id);

    /**
     * Graph validation
     */

    /**
     * @brief Validate that the graph is valid
     *
     * @return true the graph is valid and all properties are fulfilled
     * @return false the graph is not valid and at least one properties is not fulfilled
     */
    bool validate_graph();

    /**
     * @brief run a DFS analyze,
     *
     * @return true the DFS is run succesfully
     * @return false the DFS failed to be run
     */
    bool run_DFS_analyse();

    /**
     * @brief Set graph analysis dirty (the graph was modify)
     *
     */
    void set_graph_dirty(void);

    /**
     * @brief function used to visit the graph and detect cycle
     *
     * @return true the graph contain at least one circle
     * @return false no cycle found
     */
    bool DFS(const Id node_id);

    /**
     * @brief Check that the graph does not contain a cycle
     *
     * @return true the graph contain at least one circle
     * @return false no cycle found
     */
    bool is_cycle();

    /**
     * @brief Check that the graph is connected (no node detached)
     *
     * @return true the graph is connected
     * @return false the graph is not connected
     */
    bool is_connected();

    /**
     * @brief Check that the tail is reachable from the head
     *
     * @return true the tail can be reach
     * @return false the tail can't be reach
     */
    bool tail_reachable();

    /**
     * Graph structur access
     */

     /**
      * @brief Get a list of neighbors of a node
      *
      * @param node node id which neighbors are return
      * @return std::vector<Id> vector of neighbors ID
      */
    std::vector<Id> neighbors(const Id& node_id);

    /**
     * @brief Get the edges ID incoming in a node
     *
     * @param node id of the node
     * @return std::vector<Id> list of a outgoing edges
     */
    std::vector<Id> get_incoming_edges(const Id& node_id);

    /**
     * @brief Get the edges ID incoming to a node
     *
     * @param node id of the node
     * @return std::vector<Id> list of a incoming edges
     */
    std::vector<Id> get_outgoing_edges(const Id& node_id);

    /**
     * @brief Get the connections of a specific port of a specific node
     *
     * @param node ID of the node
     * @param PortID ID of the port
     * @return std::vector<Id> list of connections
     */
    std::vector<Id> get_connections(const Id& node, const Id& PortID);

    /**
     * @brief Get the string representation of the graph
     *
     * @return std::string graph representation
     */
    std::string get_str(void);

    /**
     * @brief Same as get_str(void) but with tab at each lines
     *
     * @param tab number of tab to insert
     * @return std::string graph representation
     */
    std::string get_str(const unsigned int tab);

    // Method to construc recursivly the json project file
    nlohmann::json to_json(void);

    static bool is_json_valid(const nlohmann::json& j);

    std::vector<NodeData> get_nodes_data(void);


    std::string get_node_type(const Id& id);

    PortDirection get_port_direction(const Id& node_id, const Id& port_id);

signals:
    void node_position_changed(const Id& id, const QPointF& pos);
    void node_has_been_delete(const Id& id);
    void node_has_been_added(const NodeData& data);
};

#endif