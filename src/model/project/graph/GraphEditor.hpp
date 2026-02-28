#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include "Graph.hpp"

#include <utils/Types.hpp>

class GraphEditor
{
private:
    Graph node_graph;

public:
    GraphEditor() = default;
    Id add_node(const string& node_type, unsigned int position);
    bool remove_node(const Id& node_id);
    string get_str(void);
    string get_str(const unsigned int tab);
};

#endif