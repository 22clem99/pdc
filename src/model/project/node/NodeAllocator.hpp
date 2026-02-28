#ifndef NODE_ALLOCATOR_H
#define NODE_ALLOCATOR_H

#include "NodeProperty.hpp"

#include <utils/Singleton.hpp>

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

using namespace std;

class NodeAllocator
{
public:
    static void register_node(const string& name, NodeProperty property);
    static unique_ptr<Node> alloc_node(const string& node_type);
    static optional<NodeProperty> get_property(const string& node_type);

private:
    static unordered_map<string, NodeProperty>& registry();

};

#endif