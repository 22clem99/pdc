/**
 * @file NodeAllocator.hpp
 * @brief This class Node Allocator use to allocate dynamically nodes
 */

#ifndef NODE_ALLOCATOR_H
#define NODE_ALLOCATOR_H

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

#include "NodeProperty.hpp"
#include <utils/Singleton.hpp>

/**
 * @brief NodeAllocator is a registerd factory implementation class
 *
 * Each derived class from Node need to sign in to this
 * factory and then it will be possible to dynamically
 * allocate node object.
 */
class NodeAllocator
{
public:
    /**
     * @brief Method to register a node to the factory
     *
     * @param name keyword of the object associate
     * @param property object associate with the keyword,
     * this object embed: the factory method associate
     * with the keyword and some information used by the
     * graph to avoid to allocate node uselessly.
     */
    static void register_node(const std::string& name, NodeProperty property);

    /**
     * @brief Method to allocate an object of kind Node registerd in the factory
     *
     * @param node_type keyword of the node to allocate
     * @return std::unique_ptr<Node> pointer on the new object allocate
     */
    static std::unique_ptr<Node> alloc_node(const std::string& node_type);

    /**
     * @brief Method to allocate an object of kind Node registerd in the factory
     *
     * @param node_type keyword of the node to allocate
     * @param json json file
     * @return std::unique_ptr<Node> pointer on the new object allocate
     */
    static std::unique_ptr<Node> alloc_node_json(const std::string& node_type, const nlohmann::json& j);

    /**
     * @brief Get the property object depending of the node keyword
     *
     * @param node_type node keyword
     * @return std::optional<NodeProperty> properties
     */
    static std::optional<NodeProperty> get_property(const std::string& node_type);

private:
    /**
     * @brief private function to get map corresponding to the factory registred items
     * this map is protected by a C++ singleton pattern
     *
     * @return std::unordered_map<std::string, NodeProperty>&
     */
    static std::unordered_map<std::string, NodeProperty>& registry();
};

#endif