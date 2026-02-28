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

    Edge(Id from_n, Id from_o, Id to_n, Id to_i)
    {
        from_node = from_n;
        from_output = from_o;
        to_node = to_n;
        to_input = to_i;
    }

    string get_str(void)
    {
        return get_str(0);
    }

    string get_str(const unsigned int tab) const
    {
        return "Edge {from " + from_node + "[" + from_output + "], to " + to_node +  "[" + to_input + "]}";
    }
};

#endif