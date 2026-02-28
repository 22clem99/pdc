#include "NodeAllocator.hpp"

#include <utils/Log.hpp>

void NodeAllocator::register_node(const string& name, NodeProperty property)
{
    registry()[name] = property;
}

unique_ptr<Node> NodeAllocator::alloc_node(const string& node_type)
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

std::optional<NodeProperty> NodeAllocator::get_property(const string& node_type)
{
    Log::debug("Trying to get property with node type : \"" + node_type + "\"");
    auto it = registry().find(node_type);

    if (it == registry().end()) {
        Log::debug("Node type \"" + node_type + "\" doesn't exist, return a null pointer");
        return nullopt;
    }

    Log::debug("Node type \"" + node_type + "\" exist");

    return it->second;
}

unordered_map<string, NodeProperty>& NodeAllocator::registry()
{
    static unordered_map<string, NodeProperty> instance;
    return instance;
}