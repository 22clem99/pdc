#include "Graph.hpp"
#include "../node/NodeAllocator.hpp"
#include <utils/Tab.hpp>

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

string Graph::get_str()
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

    s += s_tab + "\t}\n"
        + s_tab + "}";

    return s;
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
