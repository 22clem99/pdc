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
        : graph(g), node_id(id)
    {
        setText("Remove node");
    }

    void undo() override
    {
        data = graph->add_node(node_type, position);

        // Extract data and setup for the redo
        node_id = data.node_id;
    }

    void redo() override
    {
        // Extract data by ID
        position = graph->get_node_position(node_id);
        node_type = graph->get_node_type(node_id);

        // When edge will be managed, we will need to rewired
        // all in the undo method

        graph->remove_node(node_id);
    }

    NodeData data;

private:
    GraphEditor* graph;
    Id node_id;
    std::string node_type;
    QPointF position;

};

class MoveNodeCommand : public QUndoCommand
{
public:
    MoveNodeCommand(GraphEditor* g, const Id& id, const QPointF& pos)
        : graph(g), node_id(id), new_position(pos)
    {
        setText("Move node");
        old_position = graph->get_node_position(id);
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
#endif