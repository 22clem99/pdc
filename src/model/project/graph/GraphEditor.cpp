/**
 * @file GraphEditor.cpp
 * @brief Implementing GraphEditor class
 */

#include "GraphEditor.hpp"

GraphEditor::GraphEditor(void)
{
    // Node signals
    QObject::connect(&node_graph, &Graph::node_position_changed, this, &GraphEditor::node_position_changed);
    QObject::connect(&node_graph, &Graph::node_has_been_delete, this, &GraphEditor::node_has_been_delete);
    QObject::connect(&node_graph, &Graph::node_has_been_added, this, &GraphEditor::node_has_been_added);

    // Edge signals
    QObject::connect(&node_graph, &Graph::edge_has_been_delete, this, &GraphEditor::edge_has_been_delete);
    QObject::connect(&node_graph, &Graph::edge_has_been_added, this, &GraphEditor::edge_has_been_added);
}

GraphEditor::GraphEditor(const nlohmann::json& j) : node_graph(j)
{
    // Node signals
    QObject::connect(&node_graph, &Graph::node_position_changed, this, &GraphEditor::node_position_changed);
    QObject::connect(&node_graph, &Graph::node_has_been_delete, this, &GraphEditor::node_has_been_delete);
    QObject::connect(&node_graph, &Graph::node_has_been_added, this, &GraphEditor::node_has_been_added);

    // Edge signals
    QObject::connect(&node_graph, &Graph::edge_has_been_delete, this, &GraphEditor::edge_has_been_delete);
    QObject::connect(&node_graph, &Graph::edge_has_been_added, this, &GraphEditor::edge_has_been_added);
}

GraphEditor::~GraphEditor(void)
{
    // Disconnect incoming signals
    QObject::disconnect(nullptr, nullptr, this, nullptr);
}

NodeCreationTestStatus GraphEditor::can_add_node(const std::string& node_type)
{
    return node_graph.can_add_node(node_type);
}

NodeData GraphEditor::add_node(const std::string& node_type, const QPointF& pos)
{
    NodeData data;

    data.node_id = node_graph.add_node(node_type, pos);
    data.position = pos;
    data.pretty_print = NodeAllocator::get_pretty_print(node_type);

    return data;
}

NodeData GraphEditor::add_node_snapshot(const NodeSnapshot& snapshot)
{
    NodeData data;

    data.node_id = node_graph.add_node_snapshot(snapshot);
    data.position = snapshot.position;
    data.pretty_print = NodeAllocator::get_pretty_print(snapshot.node_type);

    return data;
}

bool GraphEditor::remove_node(const Id& node_id)
{
    return node_graph.remove_node(node_id);
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

std::vector<NodeData> GraphEditor::get_nodes_data(void)
{
    return node_graph.get_nodes_data();
}

std::string GraphEditor::get_node_type(const Id& id)
{
    return node_graph.get_node_type(id);
}

EdgeCreationTestStatus GraphEditor::can_add_edge(const Id& from_node, const Id& from_port, const Id& to_node, const Id& to_port)
{
    return node_graph.can_connect(from_node, from_port, to_node, to_port);
}

EdgeData GraphEditor::add_edge(const Id& from_node, const Id& from_port, const Id& to_node, const Id& to_port, const Id& existing_id)
{
    EdgeData data;

    data.edge_id = node_graph.connect(from_node, from_port, to_node, to_port, existing_id);
    data.node_id_dst = from_node;
    data.port_id_dst = from_port;
    data.node_id_src = to_node;
    data.port_id_src = to_port;

    return data;
}


EdgeData GraphEditor::add_edge_snapshot(const EdgeSnapshot& snap)
{
    return add_edge(snap.from_node,
                    snap.from_port,
                    snap.to_node,
                    snap.to_port,
                    snap.edge_id);
}

bool GraphEditor::remove_edge(const Id& edge_id)
{
    return node_graph.disconnect(edge_id);
}

std::vector<EdgeData> GraphEditor::get_edges_data(void)
{
    return node_graph.get_edges_data();
}

EdgeData GraphEditor::get_edge_data(const Id& id)
{
    return node_graph.get_edge_data(id);
}

std::vector<EdgeData> GraphEditor::get_edges_data_by_node(const Id& id)
{
    std::vector<EdgeData> edges_data;

    auto edges = node_graph.get_incoming_edges(id);
    auto outgoing_edges = node_graph.get_outgoing_edges(id);

    edges.insert(edges.end(), outgoing_edges.begin(), outgoing_edges.end());

    for (auto edge_id : edges)
    {
        auto edge = node_graph.edges[edge_id].get();

        edges_data.push_back(EdgeData{edge_id,
                                      edge->from_node,
                                      edge->from_output,
                                      edge->to_node,
                                      edge->to_input});
    }

    return edges_data;

}

bool GraphEditor::is_input(const Id& node_id, const Id& port_id)
{
    return (PortDirection::Input == node_graph.get_port_direction(node_id, port_id) ? true : false );
}

bool GraphEditor::is_output(const Id& node_id, const Id& port_id)
{
    return (PortDirection::Output == node_graph.get_port_direction(node_id, port_id) ? true : false );
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

NodeSnapshot GraphEditor::get_node_snapshot(const Id& id)
{
    return node_graph.get_node_snapshot(id);
}

EdgeSnapshot GraphEditor::get_edge_snapshot(const Id& id)
{
    return node_graph.get_edge_snapshot(id);
}

std::vector<EdgeSnapshot> GraphEditor::get_edges_snapshot_linked_to_node(const Id& id)
{
    std::vector<EdgeSnapshot> edges_snapshot;

    auto edges = node_graph.get_incoming_edges(id);
    auto outgoing_edges = node_graph.get_outgoing_edges(id);

    edges.insert(edges.end(), outgoing_edges.begin(), outgoing_edges.end());

    for (auto edge : edges)
    {
        edges_snapshot.push_back(node_graph.get_edge_snapshot(edge));
    }

    return edges_snapshot;
}