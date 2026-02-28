#include "GraphEditor.hpp"


Id GraphEditor::add_node(const string& node_type, unsigned int position)
{
    //TODO manage position
    return node_graph.add_node(node_type);
}

bool GraphEditor::remove_node(const Id& node_id)
{
    return node_graph.remove_node(node_id);
}

string GraphEditor::get_str(void)
{
    return get_str(0);
}

string GraphEditor::get_str(const unsigned int tab)
{
    return node_graph.get_str(tab);
}
