#include <model/project/Project.hpp>

#include <model/project/graph/Graph.hpp>
#include <model/project/node/ImageInputNode.hpp>
#include <model/project/node/ImageOutputNode.hpp>

#include <utils/Log.hpp>
#include <cassert>

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

    // Test with bad nodes ID
    assert(g.connect("", "", id_out, id_out_port) == nullid);
    assert(g.connect(id_in, id_in_port, "", "") == nullid);

    // Test with bad port
    assert(g.connect(id_in, id_in_port, id_out, "") == nullid);
    assert(g.connect(id_in, "", id_out, id_in_port) == nullid);

    // Test a good edge
    auto id_first = g.connect(id_in, id_in_port, id_out, id_out_port);
    assert(id_first != nullid);

    // Test a edge in the wrong direction
    assert(g.connect(id_out, id_out_port, id_in, id_in_port) == nullid);

    Log::info(g.get_str());

    // Test the disconnect method
    assert(g.disconnect(id_first));
    Log::info(g.get_str());

    // Rollback and add the same edge
    auto id_sec = g.connect(id_in, id_in_port, id_out, id_out_port);
    assert(id_sec != nullid);
    Log::info(g.get_str());

    return 0;
}
