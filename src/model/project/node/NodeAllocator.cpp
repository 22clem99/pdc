/**
 * @file NodeAllocator.cpp
 * @brief Implementing NodeAllocator class
 *
 */

#include <QObject>

#include "NodeAllocator.hpp"
#include <utils/Log.hpp>
#include "../graph/Graph.hpp"
#include "NodeNotifier.hpp"

void NodeAllocator::register_node(const std::string& name, NodeProperty property)
{
    registry()[name] = property;
}

std::unique_ptr<Node> NodeAllocator::alloc_node(const std::string& node_type, Graph* g)
{
    Log::debug("Trying to alloc a node of type : \"" + node_type + "\"");
    auto it = registry().find(node_type);

    if (it == registry().end()) {
        Log::debug("Node type \"" + node_type + "\" doesn't exist, return a null pointer");
        return nullptr;
    }

    Log::debug("Node type \"" + node_type + "\" exist");

    // Instantiate the node
    auto node = it->second.factory(g);

    // Set notifier
    auto notifier = new NodeNotifier(node.get());
    node->set_notifier(notifier);

    QObject::connect(node.get(),
                    &Node::position_changed,
                    notifier,
                    &NodeNotifier::node_position_changed);

    return node;

}

std::unique_ptr<Node> NodeAllocator::alloc_node_json(const std::string& node_type, const nlohmann::json& j, Graph* g)
{
    Log::debug("Trying to alloc a node with a of type : \"" + node_type + "\"");
    auto it = registry().find(node_type);

    if (it == registry().end()) {
        Log::debug("Node type \"" + node_type + "\" doesn't exist, return a null pointer");
        return nullptr;
    }

    Log::debug("Node type \"" + node_type + "\" exist");

    // Instantiate the node
    auto node = it->second.factory_json(j, g);

    // Set notifier
    auto notifier = new NodeNotifier(node.get());
    node->set_notifier(notifier);

    QObject::connect(node.get(),
                    &Node::position_changed,
                    notifier,
                    &NodeNotifier::node_position_changed);


    return node;
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

std::string NodeAllocator::get_pretty_print(const std::string& node_type)
{
    Log::debug("Trying to get property with node type : \"" + node_type + "\"");
    auto it = registry().find(node_type);

    if (it == registry().end()) {
        Log::debug("Node type \"" + node_type + "\" doesn't exist, return a null pointer");
        return nullid;
    }

    Log::debug("Node type \"" + node_type + "\" exist return the pretty print");

    return it->second.descriptor.pretty_print;
}

bool NodeAllocator::is_json_valid(const std::string& node_type, const nlohmann::json& j)
{
    auto it = registry().find(node_type);

    if (it == registry().end()) {
        Log::debug("Node type \"" + node_type + "\" doesn't exist, return false");
        return false;
    }

    return it->second.json_validator(j);
}