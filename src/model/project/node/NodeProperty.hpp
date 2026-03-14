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
    NodeDescriptor(NodeKind k, std::string pp, std::string desc)
        : kind(k), pretty_print(std::move(pp)), description(std::move(desc)) {}
    NodeDescriptor& operator=(const NodeDescriptor& other) = default;
};


/**
 * @brief This define is just to rename more consisly the allocation method call
 *
 */
typedef std::function<std::unique_ptr<Node>(QObject*)> CreatorFuncNode;

/**
 * @brief This define is just to rename more consisly the allocation method call with json param
 *
 */
typedef std::function<std::unique_ptr<Node>(const nlohmann::json&, QObject*)> CreatorFuncNodeJson;

/**
 * @brief This define is just to rename more consisly the JSON test method
 *
 */
typedef std::function<bool(const nlohmann::json&)> JsonValidator;

/**
 * @brief NodeProperty is a class to provide to the factory the allocator and data to manage allocation
 *
 */
class NodeProperty
{
public:
    CreatorFuncNode factory;
    CreatorFuncNodeJson factory_json;
    JsonValidator json_validator;

    NodeDescriptor descriptor;
};

#endif