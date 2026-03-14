/**
 * @file GraphEditor.cpp
 * @brief Implementing GraphEditor class
 */

#include "GraphEditor.hpp"

GraphEditor::GraphEditor(void)
{
    QObject::connect(&node_graph, &Graph::node_position_changed, this, &GraphEditor::node_position_changed);
}

GraphEditor::GraphEditor(const nlohmann::json& j) : node_graph(j)
{
    QObject::connect(&node_graph, &Graph::node_position_changed, this, &GraphEditor::node_position_changed);
}

GraphEditor::~GraphEditor(void)
{
    QObject::disconnect(nullptr, nullptr, this, nullptr);
}

NodeData GraphEditor::add_node(const std::string& node_type, const QPointF& pos)
{
    NodeData data;

    data.node_id = node_graph.add_node(node_type, pos);
    data.position = pos;
    data.pretty_print = NodeAllocator::get_pretty_print(node_type);

    return data;
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

void GraphEditor::set_node_position(const Id& id, const QPointF& position)
{
    auto& node = node_graph.nodes[id];

    node->set_position(position);
}

QPointF GraphEditor::get_node_position(const Id& id)
{
    auto& node = node_graph.nodes[id];

    return node->get_position();
}