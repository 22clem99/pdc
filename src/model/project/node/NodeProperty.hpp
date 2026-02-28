#ifndef NODE_PROPERTY_H
#define NODE_PROPERTY_H

#include "Node.hpp"
#include <functional>

typedef function<unique_ptr<Node>()> CreatorFunc;

class NodeProperty
{
public:
    NodeKind kind;
    CreatorFunc factory;
};

#endif