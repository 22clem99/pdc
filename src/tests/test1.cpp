#include <model/project/Project.hpp>

#include <model/project/node/Node.hpp>
#include <model/project/node/NodeAllocator.hpp>
#include <model/project/node/ImageInputNode.hpp>

#include <utils/Log.hpp>

int main(int argc, char *argv[])
{
    Log::set_level(LogLevel::DEBUG);

    Project p("My amazing project", "./images/Tux.svg");

    unique_ptr<Node> new_node = NodeAllocator::alloc_node(ImageInputNode::class_name());

    Log::info(new_node->get_str());

    return 0;
}
