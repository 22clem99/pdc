#include <model/project/Project.hpp>

#include <model/project/graph/Graph.hpp>
#include <model/project/node/ImageInputNode.hpp>
#include <model/project/node/ImageOutputNode.hpp>

#include <utils/Log.hpp>

int main(int argc, char *argv[])
{
    Log::set_level(LogLevel::DEBUG);

    Graph g;

    Id id_in = g.add_node(ImageInputNode::class_name());
    Id id_out = g.add_node(ImageOutputNode::class_name());

    auto& inPorts  = g.nodes[id_in]->ports;
    auto& outPorts = g.nodes[id_out]->ports;

    Id id_in_port = inPorts.begin()->first;
    Id id_out_port = outPorts.begin()->first;

    g.connect(id_in, id_in_port, id_out, id_out_port);

    Log::info(g.get_str());

    return 0;
}
