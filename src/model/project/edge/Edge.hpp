#ifndef EDGE_H
#define EDGE_H

#include <string>

#include <utils/Types.hpp>

using namespace std;

class Edge
{
public:
    Id from_node;
    Id from_output;

    Id to_node;
    Id to_input;

    Edge() = default;

    string get_str(void)
    {
        return get_str(0);
    }

    string get_str(const unsigned int tab)
    {
        return "Edge {from " + from_node + "[" + from_output + "], to " + to_node +  "[" + to_input + "]}";
    }
};

#endif