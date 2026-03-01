#include "Graph.hpp"
#include "../node/NodeAllocator.hpp"
#include <utils/Tab.hpp>
#include <memory>

Id Graph::add_node(const string& node_type)
{
    optional<NodeProperty> prop = NodeAllocator::get_property(node_type);

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
    unique_ptr<Node> new_node = NodeAllocator::alloc_node(node_type);
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

    nodes.insert({id, move(new_node)});

    return id;
}

bool Graph::remove_node(const Id& node_id)
{
    return false;
}

bool Graph::has_node(const Id& node_id)
{
    return false;
}

Id Graph::connect(const Id& from_node, const Id& from_output, const Id& to_node, const Id& to_input)
{
    auto& from_node_obj = *nodes[from_node];
    auto& to_node_obj = *nodes[to_node];

    auto& from_output_obj = *from_node_obj.ports[from_output];
    auto& to_input_obj = *to_node_obj.ports[to_input];

    // Test compatibility, edge need to link
    // the same type of data.
    if (!IPortBase::same_type(from_output_obj, to_input_obj))
    {
        Log::error("Node \"" + from_node + "\" and \"" + to_node + "\n are not the same type, can't be connected");

        return nullid;
    }

    // Test output mode, edge need to link
    // an output and the output kind need to
    // be <Multiple>
    if ((from_output_obj.get_direction() != PortDirection::Output)
        || (from_output_obj.get_connection_mode() != ConnectionMode::Multiple))
    {
        Log::error("Node \"" + from_node + "\" is not an Output or it's connection mode is not Multiple");
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
        Log::error("Node \"" + to_node + "\" is not an Input or it's connection mode is not Single or a edge is already connected");
        return nullid;
    }

    // All test OK, now we can create the edge
    auto new_edge = make_unique<Edge>(from_node, from_output, to_node, to_input);
    Id new_edge_id = new_edge->id;


    // Add edge in the edges vector
    edges.emplace(new_edge_id, move(new_edge));

    // TODO update connection vector in PORTS

    return new_edge_id;
}

bool Graph::disconnect(const Id& edge)
{
    return false;
}

int Graph::remove_edges_of_node(const Id& node)
{
    return false;
}

bool Graph::can_connect(const Id& from_node, const Id& from_output, const Id& to_node, const Id& from_input)
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

    /*********** Graph structur access ***********/
vector<Id> Graph::neighbors(const Id& node)
{
    vector<Id> neighbors_id = {};

    return neighbors_id;
}

vector<Id> Graph::get_incoming_edges(const Id& node)
{
    vector<Id> edges_id = {};

    return edges_id;
}

vector<Id> Graph::get_outgoing_edges(const Id& node)
{
    vector<Id> edges_id = {};

    return edges_id;
}

vector<Id> Graph::get_connections(const Id& node, const Id& PortID)
{
    return nodes[node]->ports[PortID]->get_connected_edges();
}

string Graph::get_str(void)
{
    return get_str(0);
}

string Graph::get_str(const unsigned int tab)
{
    string s_tab = Tab::tab(tab);
    string s = s_tab + "Graph {\n"
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
