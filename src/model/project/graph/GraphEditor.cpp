/**
 * @file GraphEditor.cpp
 * @brief Implementing GraphEditor class
 */

#include "GraphEditor.hpp"

GraphEditor::GraphEditor(const nlohmann::json& j)
{
    node_graph = Graph(j);
}

Id GraphEditor::add_node(const std::string& node_type, const QPointF& pos)
{
    //TODO manage position
    return node_graph.add_node(node_type, pos);
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

nlohmann::json GraphEditor::to_json(void)
{
    return node_graph.to_json();
}