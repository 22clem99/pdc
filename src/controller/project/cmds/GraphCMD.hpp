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

#endif