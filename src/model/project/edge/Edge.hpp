#ifndef EDGE_H
#define EDGE_H

#include <string>

#include <utils/Types.hpp>

using namespace std;

class Edge
{
private:
    Id from_node;
    Id from_output;

    Id to_node;
    Id to_input;
};

#endif