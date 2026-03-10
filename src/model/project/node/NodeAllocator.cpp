/**
 * @file NodeAllocator.cpp
 * @brief Implementing NodeAllocator class
 *
 */

#include "NodeAllocator.hpp"
#include <utils/Log.hpp>

void NodeAllocator::register_node(const std::string& name, NodeProperty property)
{
    registry()[name] = property;
}

std::unique_ptr<Node> NodeAllocator::alloc_node(const std::string& node_type)
{
    Log::debug("Trying to alloc a node of type : \"" + node_type + "\"");
    auto it = registry().find(node_type);

    if (it == registry().end()) {
        Log::debug("Node type \"" + node_type + "\" doesn't exist, return a null pointer");
        return nullptr;
    }

    Log::debug("Node type \"" + node_type + "\" exist");

    return it->second.factory();
}

std::unique_ptr<Node> NodeAllocator::alloc_node_json(const std::string& node_type, const nlohmann::json& j)
{
    Log::debug("Trying to alloc a node with a of type : \"" + node_type + "\"");
    auto it = registry().find(node_type);

    if (it == registry().end()) {
        Log::debug("Node type \"" + node_type + "\" doesn't exist, return a null pointer");
        return nullptr;
    }

    Log::debug("Node type \"" + node_type + "\" exist");

    return it->second.factory_json(j);
}

std::optional<NodeProperty> NodeAllocator::get_property(const std::string& node_type)
{
    Log::debug("Trying to get property with node type : \"" + node_type + "\"");
    auto it = registry().find(node_type);

    if (it == registry().end()) {
        Log::debug("Node type \"" + node_type + "\" doesn't exist, return a null pointer");
        return std::nullopt;
    }

    Log::debug("Node type \"" + node_type + "\" exist");

    return it->second;
}

std::unordered_map<std::string, NodeProperty>& NodeAllocator::registry()
{
    static std::unordered_map<std::string, NodeProperty> instance;
    return instance;
}

std::unordered_map<Id, NodeDescriptor> NodeAllocator::get_available_node(void)
{
    std::unordered_map<Id, NodeDescriptor> result;

    for (const auto& [id, prop] : registry())
    {
        result[id] = NodeDescriptor(prop.descriptor);
    }

    return result;
}