/**
 * @file NodeProperty.hpp
 * @brief Header to define the node property object used by the factory
 */

#ifndef NODE_PROPERTY_H
#define NODE_PROPERTY_H

#include <functional>

#include "Node.hpp"

/**
 * @brief This define is just to rename more consisly the allocation method call
 *
 */
typedef std::function<std::unique_ptr<Node>()> CreatorFuncNode;

/**
 * @brief NodeProperty is a class to provide to the factory the allocator and data to manage allocation
 *
 */
class NodeProperty
{
public:
    NodeKind kind;
    CreatorFuncNode factory;
};

#endif