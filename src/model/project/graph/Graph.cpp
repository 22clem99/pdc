#include "Graph.hpp"
#include "../node/NodeAllocator.hpp"

int Graph::add_node(const string& node_type, int position)
{
    unique_ptr<Node> new_node = NodeAllocator::alloc_node(node_type);

    return 0;
}

int Graph::remove_node(const Id& node_id)
{
    return 0;
}

string Graph::get_str(void)
{
    return "";
}
