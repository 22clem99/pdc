/**
 * @file NodeProperty.hpp
 * @brief Header to define the node property object used by the factory
 */

#ifndef NODE_PROPERTY_H
#define NODE_PROPERTY_H

#include <functional>

#include "Node.hpp"

class NodeDescriptor
{
public:
    NodeKind kind;
    std::string pretty_print;
    std::string description;

    NodeDescriptor() = default;
    NodeDescriptor(const NodeDescriptor& other) = default;
    NodeDescriptor& operator=(const NodeDescriptor& other) = default;
};


/**
 * @brief This define is just to rename more consisly the allocation method call
 *
 */
typedef std::function<std::unique_ptr<Node>()> CreatorFuncNode;

/**
 * @brief This define is just to rename more consisly the allocation method call with json param
 *
 */
typedef std::function<std::unique_ptr<Node>(const nlohmann::json&)> CreatorFuncNodeJson;

/**
 * @brief NodeProperty is a class to provide to the factory the allocator and data to manage allocation
 *
 */
class NodeProperty
{
public:
    CreatorFuncNode factory;
    CreatorFuncNodeJson factory_json;

    NodeDescriptor descriptor;
};

#endif