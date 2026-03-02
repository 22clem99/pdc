#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <map>
#include <memory>

#include <utils/Types.hpp>

#include "../node/Node.hpp"
#include "../edge/Edge.hpp"


/**
 * @brief Graph object, represent nodes and edges.
 * This graph have specific properties:
 * - oriented
 * - single-entry single-exit graph (named head and tail)
 * - acyclic
 */
class Graph
{
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

    /**
     *  Nodes manipulation
     */

    /**
     * @brief Allocate a node and store it in the graph
     *
     * @param node_type node name to allocate, it will be used by the factory
     * @return Id generate for this new Node
     */
    Id add_node(const std::string& node_type);

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
    bool disconnect(const Id& edge);

    /**
     * @brief Remove all edges connected to a node
     *
     * @param node node ID to clear edges
     * @return int number of edges removed
     */
    int remove_edges_of_node(const Id& node);

    /**
     * Graph validation
     */

    /**
     * @brief Validate that the graph is valid
     *
     * @return true the graph is valid and all properties are fulfilled
     * @return false the graph is not valid and at least one properties is not fulfilled
     */
    bool validateGraph();

    /**
     * @brief Check that the graph does not contain a cycle
     *
     * @return true the graph contain at least one circle
     * @return false no cycle found
     */
    bool is_cycle();

    /**
     * Graph structur access
     */

     /**
      * @brief Get a list of neighbors of a node
      *
      * @param node node id which neighbors are return
      * @return std::vector<Id> vector of neighbors ID
      */
    std::vector<Id> neighbors(const Id& node);

    /**
     * @brief Get the edges ID incoming in a node
     *
     * @param node id of the node
     * @return std::vector<Id> list of a outgoing edges
     */
    std::vector<Id> get_incoming_edges(const Id& node);

    /**
     * @brief Get the edges ID incoming to a node
     *
     * @param node id of the node
     * @return std::vector<Id> list of a incoming edges
     */
    std::vector<Id> get_outgoing_edges(const Id& node);

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
};

#endif