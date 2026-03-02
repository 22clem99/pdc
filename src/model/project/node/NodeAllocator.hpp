#ifndef NODE_ALLOCATOR_H
#define NODE_ALLOCATOR_H

#include "NodeProperty.hpp"

#include <utils/Singleton.hpp>

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>



class NodeAllocator
{
public:
    static void register_node(const std::string& name, NodeProperty property);
    static std::unique_ptr<Node> alloc_node(const std::string& node_type);
    static std::optional<NodeProperty> get_property(const std::string& node_type);

private:
    static std::unordered_map<std::string, NodeProperty>& registry();

};

#endif