#include <QPointF>
#include <cassert>

#include <model/project/Project.hpp>

#include <model/project/graph/Graph.hpp>
#include <model/project/node/ImageInputNode.hpp>
#include <model/project/node/ImageOutputNode.hpp>

#include <utils/Log.hpp>

int main(int argc, char *argv[])
{
    Log::set_level(LogLevel::Debug);

    Graph g;

    Id id_out = g.add_node(ImageOutputNode::class_name(), QPointF(0, 0));
    auto& outPorts = g.nodes[id_out]->ports;
    Id id_out_port = outPorts.begin()->first;

    assert(g.validate_graph() == false);

    Id id_in = g.add_node(ImageInputNode::class_name(), QPointF(0, 0));
    auto& inPorts  = g.nodes[id_in]->ports;
    Id id_in_port = inPorts.begin()->first;

    auto id_first = g.connect(id_in, id_in_port, id_out, id_out_port);
    assert(id_first != nullid);

    Log::info(g.get_str());

    assert(g.validate_graph() == true);

    return 0;
}
