#ifndef GRAPH_CMD_H
#define GRAPH_CMD_H

#include <QUndoCommand>
#include <string>

#include "../../../model/project/graph/GraphEditor.hpp"

class AddNodeCommand : public QUndoCommand
{
public:
    AddNodeCommand(GraphEditor* g, const std::string& type, const QPointF& pos)
        : graph(g), node_type(type), position(pos)
    {
        setText("Add node");
    }

    void undo() override
    {
        graph->remove_node(data.node_id);
    }

    void redo() override
    {
        data = graph->add_node(node_type, position);
    }

    NodeData data;

private:
    GraphEditor* graph;
    std::string node_type;
    QPointF position;

};

class RemoveNodeCommand : public QUndoCommand
{
public:
    RemoveNodeCommand(GraphEditor* g, const Id& id)
        : graph(g)
    {
        setText("Remove node");

        // Extract snapshot data before to remove nodes and edges
        node_snapshot = graph->get_node_snapshot(id);
        edges_snapshot = graph->get_edges_snapshot_linked_to_node(id);
    }

    void undo() override
    {
        // First roleback the node removing
        data = graph->add_node_snapshot(node_snapshot);

        // Then recreate all edges by snapshot
        for (auto edge : edges_snapshot)
        {
            graph->add_edge_snapshot(edge);
        }
    }

    void redo() override
    {
        // Call the remove node function, this will also remove edges
        // wired to the node
        graph->remove_node(node_snapshot.node_id);
    }

    NodeData data;

private:
    GraphEditor* graph;

    NodeSnapshot node_snapshot;
    std::vector<EdgeSnapshot> edges_snapshot;//edges_linked_to_node;
};

class MoveNodeCommand : public QUndoCommand
{
public:
    MoveNodeCommand(GraphEditor* g, const Id& id, const QPointF& pos)
        : graph(g), node_id(id), new_position(pos)
    {
        setText("Move node");
        old_position = graph->get_node_position(id);

        Log::debug("Create a move cmd with: old " + std::to_string(old_position.x()) + ", " + std::to_string(old_position.y()) + " et new " + std::to_string(new_position.x()) + ", " + std::to_string(new_position.y()));
    }

    void undo() override
    {
        graph->set_node_position(node_id, old_position);
    }

    void redo() override
    {
        graph->set_node_position(node_id, new_position);
    }

    NodeData data;

private:
    GraphEditor* graph;
    Id node_id;
    QPointF old_position;
    QPointF new_position;
};

class AddEdgeCommand : public QUndoCommand
{
public:
    AddEdgeCommand(GraphEditor* g, const Id& src_node, const Id& src_port, const Id& dst_node, const Id& dst_port)
        : graph(g), from_node(src_node) ,from_port(src_port) ,to_node(dst_node) ,to_port(dst_port)
    {
        setText("Add edge");
    }

    void undo() override
    {
        graph->remove_edge(data.edge_id);
    }

    void redo() override
    {
        data = graph->add_edge(from_node, from_port, to_node, to_port);
    }

    EdgeData data;

private:
    GraphEditor* graph;
    Id from_node;
    Id from_port;
    Id to_node;
    Id to_port;
};

class RemoveEdgeCommand : public QUndoCommand
{
public:
    RemoveEdgeCommand(GraphEditor* g, const Id& id)
        : graph(g), edge_id(id)
    {
        setText("Remove edge");

        // Extract snapshot data before to remove nodes and edges
        edge_data = graph->get_edge_snapshot(id);
    }

    void undo() override
    {
        data = graph->add_edge_snapshot(edge_data);
    }

    void redo() override
    {
        // Remove edge
        graph->remove_edge(edge_data.edge_id);
    }

    EdgeData data;

private:
    GraphEditor* graph;
    Id edge_id;

    EdgeSnapshot edge_data;
};

#endif