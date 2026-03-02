#include "GraphEditor.hpp"


Id GraphEditor::add_node(const std::string& node_type, unsigned int position)
{
    //TODO manage position
    return node_graph.add_node(node_type);
}

bool GraphEditor::remove_node(const Id& node_id)
{
    return node_graph.remove_node(node_id);
}

std::string GraphEditor::get_str(void)
{
    return get_str(0);
}

std::string GraphEditor::get_str(const unsigned int tab)
{
    return node_graph.get_str(tab);
}
