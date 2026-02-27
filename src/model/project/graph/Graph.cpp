#include "Graph.hpp"
#include "../node/NodeAllocator.hpp"

Id Graph::add_node(const string& node_type)
{
    unique_ptr<Node> new_node = NodeAllocator::alloc_node(node_type);
    Id id = new_node->id;

    if(new_node == nullptr) {
        Log::error("Can't allocate node of type \"" + node_type +"\"");
    }

    nodes.insert({id, move(new_node)});

    return id;
}

bool Graph::remove_node(const Id& node_id)
{
    return false;
}

string Graph::get_str(void)
{
    return "";
}

bool Graph::has_node(const Id& node_id)
{
    return false;
}

Id Graph::connect(const Id& from_node, const Id& from_output, const Id& to_node, const Id& from_input)
{
    return "false";
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
