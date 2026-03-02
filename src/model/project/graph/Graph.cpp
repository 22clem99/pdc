/**
 * @file Graph.cpp
 * @brief Implementation of class Graph
 */

#include <memory>

#include "Graph.hpp"
#include "../node/NodeAllocator.hpp"
#include <utils/Tab.hpp>

Id Graph::add_node(const std::string& node_type)
{
    // Get factory configuration by the name
    std::optional<NodeProperty> prop = NodeAllocator::get_property(node_type);

    if (!prop) {
        Log::error("Can't allocate node of type \"" + node_type +"\"");
        return nullid;
    }

    if (prop->kind == NodeKind::Head && head_id) {
        Log::error("Can't allocate node of type \"" + node_type +"\", head node already exist");
        return nullid;
    }

    if (prop->kind == NodeKind::Tail && tail_id) {
        Log::error("Can't allocate node of type \"" + node_type +"\", tail node already exist");
        return nullid;
    }

    // Allocation is done there
    std::unique_ptr<Node> new_node = NodeAllocator::alloc_node(node_type);
    Id id = new_node->id;

    if(new_node == nullptr) {
        Log::error("Can't allocate node of type \"" + node_type +"\"");
    }

    if(prop->kind == NodeKind::Head) {
        head_id = id;
        Log::debug("The node:\"" + id + "\" is set as the head");
    }

    if(prop->kind == NodeKind::Tail) {
        tail_id = id;
        Log::debug("The node:\"" + id + "\" is set as the tail");
    }

    nodes.insert({id, std::move(new_node)});

    return id;
}

bool Graph::remove_node(const Id& node_id)
{
    return false;
}

bool Graph::has_node(const Id& node_id)
{
    return nodes.find(node_id) != nodes.end();
}

bool Graph::has_port(const Id& node_id, const Id& port_id)
{
    return nodes[node_id]->ports.find(port_id) != nodes[node_id]->ports.end();
}

bool Graph::has_edge(const Id& edge_id)
{
    return edges.find(edge_id) != edges.end();
}

Id Graph::connect(const Id& from_node, const Id& from_output, const Id& to_node, const Id& to_input)
{
    // Test IDs before to do anything
    if (!has_node(from_node))
    {
        Log::error("from node \"" + from_node + "\"is not a correct ID");
        return nullid;
    }
    if (!has_node(to_node))
    {
        Log::error("to node \"" + to_node + "\" is not a correct ID");
        return nullid;
    }
    if (!has_port(from_node, from_output) || !has_port(to_node, to_input))
    {
        Log::error("Port \"" + from_output + "\" is not a correct ID");
        return nullid;
    }
    if (!has_port(from_node, from_output) || !has_port(to_node, to_input))
    {
        Log::error("Port \"" + to_input + "\" is not a correct ID");
        return nullid;
    }

    auto& from_node_obj = *nodes[from_node];
    auto& to_node_obj = *nodes[to_node];

    auto& from_output_obj = *from_node_obj.ports[from_output];
    auto& to_input_obj = *to_node_obj.ports[to_input];

    // Test compatibility, edge need to link
    // the same type of data.
    if (!IPortBase::same_type(from_output_obj, to_input_obj))
    {
        Log::error("Node \"" + from_node + "\" and \"" + to_node + "\" are not the same type, can't be connected");
        return nullid;
    }

    // Test output mode, edge need to link
    // an output and the output kind need to
    // be <Multiple>
    if ((from_output_obj.get_direction() != PortDirection::Output)
        || (from_output_obj.get_connection_mode() != ConnectionMode::Multiple))
    {
        Log::error("Node \"" + from_output + "\" is not an Output or it's connection mode is not Multiple");
        return nullid;
    }

    // Test input mode, edge need to link
    // to an input, the input kind need to
    // be <Single> and the input port need
    // to be available (i.e any connection
    // is binded to this port)
    if ((to_input_obj.get_direction() != PortDirection::Input)
        || (to_input_obj.get_connection_mode() != ConnectionMode::Single)
        || (!to_input_obj.get_connected_edges().empty()))
    {
        Log::error("Node \"" + to_input + "\" is not an Input or it's connection mode is not Single or a edge is already connected");
        return nullid;
    }

    // All test OK, now we can create the edge
    auto new_edge = std::make_unique<Edge>(from_node, from_output, to_node, to_input);
    Id new_edge_id = new_edge->id;

    // Add edge in the edges vector
    edges.emplace(new_edge_id, std::move(new_edge));

    // Then link ports to the new edge
    from_output_obj.add_connected_edge(new_edge_id);
    to_input_obj.add_connected_edge(new_edge_id);

    return new_edge_id;
}

bool Graph::disconnect(const Id& edge)
{
    if (!has_edge(edge))
    {
        Log::debug("The edge \"" + edge + "\" is not part of this graph");
        return false;
    }

    // First clear link in ports
    auto& edge_obj = edges[edge];

    auto& port_from_obj = nodes[edge_obj->from_node]->ports;
    auto& ports_to_obj = nodes[edge_obj->to_node]->ports;

    auto& port_from = *port_from_obj[edge_obj->from_output];
    auto& port_to = *ports_to_obj[edge_obj->to_input];

    if ((port_from.remove_connected_edge(edge) != 1) || (port_to.remove_connected_edge(edge) != 1))
    {
        Log::warning("Unable to remove links on nodes\"" + edge_obj->from_node + "\" and \"" + edge_obj->to_node + "\", will continue to remove the edge but with risk");
    }

    // Then erase the edge from the edge map
    if (edges.erase(edge) != 1)
    {
        Log::warning("Unable to remove the edge\"" + edge + "\"");
        return false;
    }

    return true;
}

int Graph::remove_edges_of_node(const Id& node)
{
    return false;
}

bool Graph::validateGraph()
{
    return false;
}

bool Graph::is_cycle()
{
    return false;
}

std::vector<Id> Graph::neighbors(const Id& node)
{
    std::vector<Id> neighbors_id = {};

    return neighbors_id;
}

std::vector<Id> Graph::get_incoming_edges(const Id& node)
{
    std::vector<Id> edges_id = {};

    return edges_id;
}

std::vector<Id> Graph::get_outgoing_edges(const Id& node)
{
    std::vector<Id> edges_id = {};

    return edges_id;
}

std::vector<Id> Graph::get_connections(const Id& node, const Id& PortID)
{
    return nodes[node]->ports[PortID]->get_connected_edges();
}

std::string Graph::get_str(void)
{
    return get_str(0);
}

std::string Graph::get_str(const unsigned int tab)
{
    std::string s_tab = Tab::tab(tab);
    std::string s = s_tab + "Graph {\n"
                + s_tab + "\tNodes {\n";

    for (auto node = nodes.begin(); node != nodes.end(); node++) {
        s += node->second->get_str(tab + 2) + "\n";
    }

    s += s_tab + "\t},\n"
        + s_tab + "\tEdges {\n";

    for (auto edge = edges.begin(); edge != edges.end(); edge++) {
        s += edge->second->get_str(tab + 1) + "\n";
    }

    s += s_tab + "\t}\n";

    if (head_id)
        s += s_tab + "\thead: \"" + head_id.value() + "\",\n";

    if (tail_id)
        s += s_tab + "\ttail: \"" + tail_id.value() + "\",\n";

    s += s_tab + "}";

    return s;
}
