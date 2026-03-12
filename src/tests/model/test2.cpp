#include <model/project/Project.hpp>

#include <model/project/node/Node.hpp>
#include <model/project/node/NodeAllocator.hpp>
#include <model/project/node/ImageInputNode.hpp>
#include <model/project/node/ImageOutputNode.hpp>

#include <utils/Log.hpp>

int main(int argc, char *argv[])
{
    Log::set_level(LogLevel::Debug);

    Project p("My amazing project", std::filesystem::path("./test0/prj"), std::filesystem::path("./images/Tux.svg"));

    p.add_node(ImageInputNode::class_name(), QPointF(0, 0));
    p.add_node(ImageInputNode::class_name(), QPointF(0, 0));

    p.add_node(ImageOutputNode::class_name(), QPointF(0, 0));
    p.add_node(ImageOutputNode::class_name(), QPointF(0, 0));

    Log::info(p.get_str());

    return 0;
}
