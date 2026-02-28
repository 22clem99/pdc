#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <map>
#include <memory>

#include <utils/Types.hpp>

#include "../node/Node.hpp"
#include "../edge/Edge.hpp"

using namespace std;


class Graph
{
public:
    /// @brief Map of nodes
    map<Id, unique_ptr<Node>> nodes;
    /// @brief Map of edges between nodes
    map<Id, unique_ptr<Edge>> edges;

    Id head;
    Id tail;

    Graph() = default;

    /*********** Nodes manipulation ***********/

    /// @brief Allocate a node and store it in the graph
    /// @param node_type node name to allocate, it will be used by the factory
    /// @return the Id generate for this new Node
    Id add_node(const string& node_type);

    /// @brief remove the node and edges bind to it
    /// @param node_id node Id to be removed
    /// @return true if the value is removed succesfully otherwise false
    bool remove_node(const Id& node_id);

    /// @brief test if the node exist
    /// @param node_id node Id to be tested
    /// @return true if the node exist otherwise false
    bool has_node(const Id& node_id);

    /*********** Edges manipulation ***********/

    /// @brief connect two nodes with an edge
    /// @param from_node edge start node
    /// @param from_output output from the start node
    /// @param to_node edge end node
    /// @param from_input input from the end node
    /// @return Id of the new edge create
    Id connect(const Id& from_node, const Id& from_output, const Id& to_node, const Id& from_input);

    /// @brief remove an edge by ID
    /// @param edge edge ID tyo be removed
    /// @return
    bool disconnect(const Id& edge);

    /// @brief remove all
    /// @param node
    /// @return
    int remove_edges_of_node(const Id& node);


    /*********** Graph validation ***********/
    bool can_connect(const Id& from_node, const Id& from_output, const Id& to_node, const Id& from_input);

    /*********** Graph validation ***********/
    bool validateGraph();
    bool is_cycle();



    /// @brief Get a string representation of the Graph
    /// @return the string representation
    string get_str();
    string get_str(const unsigned int tab);
};

#endif