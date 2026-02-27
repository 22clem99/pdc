#include <model/project/Project.hpp>

#include <model/project/node/Node.hpp>
#include <model/project/node/NodeAllocator.hpp>
#include <model/project/node/ImageInputNode.hpp>

#include <utils/Log.hpp>

int main(int argc, char *argv[])
{
    Log::set_level(LogLevel::DEBUG);

    Project p("My amazing project", "./images/Tux.svg");

    p.add_node(ImageInputNode::class_name(), -1);

    Log::info(p.get_str());

    return 0;
}
