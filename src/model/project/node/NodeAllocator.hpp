#ifndef NODE_ALLOCATOR_H
#define NODE_ALLOCATOR_H

#include "Node.hpp"

#include <utils/Singleton.hpp>

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

using namespace std;

typedef function<unique_ptr<Node>()> CreatorFunc;

class NodeAllocator
{
public:
    static void register_node(const string& name, CreatorFunc func);
    static unique_ptr<Node> alloc_node(const string& node_type);

private:
    static unordered_map<string, CreatorFunc>& registry();

};

#endif