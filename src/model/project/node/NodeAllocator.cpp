#include "NodeAllocator.hpp"

#include <utils/Log.hpp>

void NodeAllocator::register_node(string name, CreatorFunc func)
{
    registry()[name] = func;
}

unique_ptr<Node> NodeAllocator::alloc_node(string node_type)
{
    Log::debug("Trying to alloc a node of type : \"" + node_type + "\"");
    auto it = registry().find(node_type);

    if (it != registry().end())
        Log::debug("Node type \"" + node_type + "\" exist, a new object will be allocate");
        return it->second();

    Log::debug("Node type \"" + node_type + "\" doesn't exist, return a null pointer");

    return nullptr;
}

unordered_map<string, CreatorFunc>& NodeAllocator::registry()
{
    static unordered_map<string, CreatorFunc> instance;
    return instance;
}