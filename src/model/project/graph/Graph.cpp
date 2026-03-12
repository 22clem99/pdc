/**
 * @file Graph.cpp
 * @brief Implementation of class Graph
 */

#include <memory>

#include "Graph.hpp"
#include "../node/NodeAllocator.hpp"
#include <utils/Tab.hpp>
#include "utils/JSONWrapper.hpp"

Graph::Graph(const nlohmann::json& j)
{
    // Iterate on each node
    for (const auto& node : j["nodes"])
    {
        std::unique_ptr<Node> new_node = NodeAllocator::alloc_node_json(node["node_type"], node);

        if(new_node == nullptr) {
           Log::error("Can't allocate node of type \"" + node["node_type"].get<std::string>() + "\"");
        }

        Id id = new_node->id;
        nodes.insert({id, std::move(new_node)});
    }

    // Iterate on each edge
    for (const auto& edge : j["edges"])
    {
        auto new_edge = std::make_unique<Edge>(edge);

        if(new_edge == nullptr) {
            Log::error("Can't allocate edge");
        }

        Id new_edge_id = new_edge->id;

        auto& from_node_obj = *nodes[new_edge->from_node];
        auto& to_node_obj = *nodes[new_edge->to_node];

        auto& from_output_obj = *from_node_obj.ports[new_edge->from_output];
        auto& to_input_obj = *to_node_obj.ports[new_edge->to_input];

        from_output_obj.add_connected_edge(new_edge_id);
        to_input_obj.add_connected_edge(new_edge_id);

        // Add edge in the edges vector
        edges.emplace(new_edge_id, std::move(new_edge));
    }
}

Id Graph::add_node(const std::string& node_type, const QPointF& pos)
{
    // Get factory configuration by the name
    std::optional<NodeProperty> prop = NodeAllocator::get_property(node_type);

    if (!prop) {
        Log::error("Can't allocate node of type \"" + node_type +"\"");
        return nullid;
    }

    if (prop->descriptor.kind == NodeKind::Head && head_id) {
        Log::error("Can't allocate node of type \"" + node_type + "\", head node already exist");
        return nullid;
    }

    if (prop->descriptor.kind == NodeKind::Tail && tail_id) {
        Log::error("Can't allocate node of type \"" + node_type + "\", tail node already exist");
        return nullid;
    }

    // Allocation is done there
    std::unique_ptr<Node> new_node = NodeAllocator::alloc_node(node_type);

    if(new_node == nullptr) {
        Log::error("Can't allocate node of type \"" + node_type + "\"");
    }

    Id id = new_node->id;

    if(prop->descriptor.kind == NodeKind::Head) {
        head_id = id;
        Log::debug("The node:\"" + id + "\" is set as the head");
    }

    if(prop->descriptor.kind == NodeKind::Tail) {
        tail_id = id;
        Log::debug("The node:\"" + id + "\" is set as the tail");
    }

    new_node->position = pos;

    nodes.insert({id, std::move(new_node)});
    analysis.analysis_dirty = true;

    return id;
}

bool Graph::remove_node(const Id& node_id)
{
    if (!has_node(node_id))
    {
        Log::debug("The node \"" + node_id + "\" is not part of this graph");
        return false;
    }

    // First remove all edges connected to the node
    remove_edges_of_node(node_id);

    // If the node is the head, remove the head
    if (head_id == node_id)
        head_id.reset();

    // If the node is the tail, remove the tail
    if (tail_id == node_id)
        tail_id.reset();

    // Then remove the node from the node list
    if (nodes.erase(node_id) != 1)
    {
        Log::debug("Unable to remove the node \"" + node_id + "\" from the graph");
        return false;
    }

    analysis.analysis_dirty = true;

    return true;
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

    if(new_edge == nullptr) {
        Log::error("Can't allocate edge");
    }

    Id new_edge_id = new_edge->id;

    // Add edge in the edges vector
    edges.emplace(new_edge_id, std::move(new_edge));

    // Then link ports to the new edge
    from_output_obj.add_connected_edge(new_edge_id);
    to_input_obj.add_connected_edge(new_edge_id);

    analysis.analysis_dirty = true;

    return new_edge_id;
}

bool Graph::disconnect(const Id& edge_id)
{
    if (!has_edge(edge_id))
    {
        Log::debug("The edge \"" + edge_id + "\" is not part of this graph");
        return false;
    }

    // First clear link in ports
    auto& edge_obj = edges[edge_id];

    auto& port_from_obj = nodes[edge_obj->from_node]->ports;
    auto& ports_to_obj = nodes[edge_obj->to_node]->ports;

    auto& port_from = *port_from_obj[edge_obj->from_output];
    auto& port_to = *ports_to_obj[edge_obj->to_input];

    if ((port_from.remove_connected_edge(edge_id) != 1) || (port_to.remove_connected_edge(edge_id) != 1))
    {
        Log::warning("Unable to remove links on nodes\"" + edge_obj->from_node + "\" and \"" + edge_obj->to_node + "\", will continue to remove the edge but with risk");
    }

    // Then erase the edge from the edge map
    if (edges.erase(edge_id) != 1)
    {
        Log::warning("Unable to remove the edge\"" + edge_id + "\"");
        return false;
    }

    analysis.analysis_dirty = true;

    return true;
}

int Graph::remove_edges_of_node(const Id& node_id)
{
    if (!has_node(node_id))
    {
        Log::debug("The node \"" + node_id + "\" is not part of this graph");
        return 0;
    }

    auto& node = nodes[node_id];
    int cnt = 0;

    for (auto& port : node->ports)
    {
        for (auto& connected_edge : port.second->get_connected_edges())
        {
            if (!disconnect(connected_edge))
            {
                Log::warning("Unable to disconect edge \"" + connected_edge + "\" from node \"" + node_id + "\"");
            }
            cnt++;
        }
    }

    return cnt;
}

bool Graph::validate_graph()
{
    // Head must be set
    if (!head_id)
    {
        Log::debug("The head is not set");
        return false;
    }

    // Tail must be set
    if (!tail_id)
    {
        Log::debug("The tail is not set");
        return false;
    }

    // Test Cycle
    if (is_cycle())
    {
        Log::debug("The graph has at least one cycle");
        return false;
    }

    // Test connected
    if (!is_connected())
    {
        Log::debug("The graph is not connected");
        return false;
    }

    // Test that the tail can be reach from the head
    if (!tail_reachable())
    {
        Log::debug("The tail can't be reach from the head");
        return false;
    }

    Log::debug("The graph si valid");
    return true;
}

bool Graph::run_DFS_analyse()
{
    // First clear all boolean used to traversing graph
    for (auto& [id, node] : nodes)
    {
        node->clear_visit_status();
    }

    // Run the DFS algorythm and check cycle
    if (DFS(head_id.value()))
    {
        analysis.has_cycle = true;
    }

    // Check that all node were visited
    analysis.is_connected = true;
    for (auto& [id, node] : nodes)
    {
        if (node->get_visit_status() == VisitState::NotVisited)
        {
            analysis.is_connected = false;
            break;
        }
    }

    // Check that tail was visited, yes it is redundant with the previous test
    analysis.tail_reachable = true;
    if (nodes[tail_id.value()]->get_visit_status() == VisitState::NotVisited)
    {
        analysis.tail_reachable = false;
    }

    // The analysis is valid
    analysis.analysis_dirty = false;

    return true;
}

void Graph::set_graph_dirty(void)
{
    analysis.analysis_dirty = true;
}

bool Graph::DFS(const Id node_id)
{
    auto& node = *nodes[node_id];

    node.set_visit_status(VisitState::Visiting);

    for (Id neighbors_id : neighbors(node_id))
    {
        if (nodes[neighbors_id]->get_visit_status() == VisitState::Visiting)
        {
            return true;
        }

        if (nodes[neighbors_id]->get_visit_status() == VisitState::NotVisited)
        {
            if (DFS(neighbors_id))
            {
                return true;
            }
        }
    }

    node.set_visit_status(VisitState::Visited);

    return false;
}

bool Graph::is_cycle()
{
    if (analysis.analysis_dirty)
        run_DFS_analyse();

    // Use the DFS analysis
    return analysis.has_cycle;
}

bool Graph::is_connected()
{
    if (analysis.analysis_dirty)
        run_DFS_analyse();

    // Use the DFS analysis
    return analysis.is_connected;
}

bool Graph::tail_reachable()
{
    if (analysis.analysis_dirty)
        run_DFS_analyse();

    // Use the DFS analysis
    return analysis.tail_reachable;
}

std::vector<Id> Graph::neighbors(const Id& node_id)
{
    std::vector<Id> neighbors_id = {};

    if (!has_node(node_id))
    {
        Log::debug("The node \"" + node_id + "\" is not part of this graph");
        return neighbors_id;
    }

    auto& node = *nodes[node_id];

    for (auto& [port_id, port] : node.ports)
    {
        for (auto& connected_edge : port->get_connected_edges())
        {
            auto& edge = *edges[connected_edge];

            if (edge.from_node == node_id)
            {
                neighbors_id.push_back(edge.to_node);
            }
        }
    }

    return neighbors_id;
}

std::vector<Id> Graph::get_incoming_edges(const Id& node_id)
{
    std::vector<Id> edges_id = {};

    // Get inputs port
    auto inputs_port = nodes[node_id]->get_ports_from_direction(PortDirection::Input);

    for (auto input_port : inputs_port)
    {
        auto port_conn_edges = nodes[node_id]->ports[input_port]->get_connected_edges();

        if (!port_conn_edges.empty())
        {
            edges_id.insert(port_conn_edges.end(), port_conn_edges.begin(), port_conn_edges.end());
        }
    }

    return edges_id;
}

std::vector<Id> Graph::get_outgoing_edges(const Id& node_id)
{
    std::vector<Id> edges_id = {};

    // Get outputs port
    auto outputs_port = nodes[node_id]->get_ports_from_direction(PortDirection::Output);

    for (auto output_port : outputs_port)
    {
        auto port_conn_edges = nodes[node_id]->ports[output_port]->get_connected_edges();

        if (!port_conn_edges.empty())
        {
            edges_id.insert(port_conn_edges.end(), port_conn_edges.begin(), port_conn_edges.end());
        }
    }

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

nlohmann::json Graph::to_json(void)
{
    using nlohmann::json;

    json graph_as_json;

    // First append nodes
    json nodes_array = json::array();

    for (auto& node : nodes)
    {
        nodes_array.push_back(node.second->to_json());
    }

    // Then append edges
    json edges_array = json::array();

    for (auto& edge : edges)
    {
        edges_array.push_back(edge.second->to_json());
    }

    return {{"nodes", nodes_array}, {"edges", edges_array}};
}

bool Graph::is_json_valid(const nlohmann::json& j)
{
    if (!j.is_object())
    {
        return false;
    }

    JSON_REQUIRED_FIELD(j, "nodes", is_array);


    Log::debug("Json parsing: Nodes list is there, continue with the node list analyse");

    // Iterate on each node
    for (const auto& node : j["nodes"])
    {
        JSON_REQUIRED_FIELD(node, "id", is_string);
        JSON_REQUIRED_FIELD(node, "node_type", is_string);
        JSON_REQUIRED_FIELD(node, "ports", is_array);

        Log::debug("Json parsing: node id, type and ports are there, continue with the port analyse");

        // First get the node_type
        auto node_type = node["node_type"];

        Log::debug("Node type read: " + node_type.dump());

        // then call the verification with the node allocator
        if (!NodeAllocator::is_json_valid(node_type, node))
        {
            return false;
        }
    }

    JSON_REQUIRED_FIELD(j, "edges", is_array);

    // Iterate on each edge
    for (const auto& edge : j["edges"])
    {
        if (!Edge::is_json_valid(edge))
            return false;
    }

    return true;
}