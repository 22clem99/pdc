#ifndef NODE_REGISTER_H
#define NODE_REGISTER_H


#include "NodeAllocator.hpp"
#include "NodeProperty.hpp"

template<typename node>
class NodeRegister
{
public:
    NodeRegister()
    {
        NodeAllocator::register_node(node::class_name(), {node::kind, []()
        {
            return make_unique<node>();
        }});
    }
};

#endif
