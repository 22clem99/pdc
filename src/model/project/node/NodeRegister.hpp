#ifndef NODE_REGISTER_H
#define NODE_REGISTER_H


#include "NodeAllocator.hpp"

template<typename node>
class NodeRegister
{
public:
    NodeRegister()
    {
        NodeAllocator::register_node(node::class_name(), []()
        {
            return make_unique<node>();
        });
    }
};

#endif
