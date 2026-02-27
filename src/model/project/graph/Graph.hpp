#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <map>
#include <memory>

#include <utils/Types.hpp>

#include "../node/Node.hpp"
#include "../edge/Edge.hpp"

using namespace std;


class Graph
{
public:
    map<string, unique_ptr<Node>> nodes;
    map<string, unique_ptr<Edge>> edges;

    Graph() = default;

    int add_node(const string& node_type, int position);
    int remove_node(const Id& node_id);

    string get_str(void);
};

#endif