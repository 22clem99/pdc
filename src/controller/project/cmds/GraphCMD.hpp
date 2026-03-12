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
        graph->remove_node(node_id);
    }

    void redo() override
    {
        node_id = graph->add_node(node_type, position);
    }

private:
    GraphEditor* graph;
    std::string node_type;
    QPointF position;

    Id node_id;
};

#endif