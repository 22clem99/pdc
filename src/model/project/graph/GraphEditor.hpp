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
    Id add_node(const std::string& node_type, unsigned int position);
    bool remove_node(const Id& node_id);
    std::string get_str(void);
    std::string get_str(const unsigned int tab);
};

#endif