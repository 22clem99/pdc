#include <model/project/Project.hpp>

#include <model/project/graph/Graph.hpp>
#include <model/project/node/ImageInputNode.hpp>
#include <model/project/node/ImageOutputNode.hpp>
#include <model/project/node/ImageRGBSplitterNode.hpp>
#include <model/project/node/ImageRGBCombinerNode.hpp>

#include <utils/Log.hpp>
#include <cassert>

int main(int argc, char *argv[])
{
    Log::set_level(LogLevel::Debug);

    Graph g;

    Id id_in = g.add_node(ImageInputNode::class_name());
    Id id_out = g.add_node(ImageOutputNode::class_name());
    Id id_split = g.add_node(ImageRGBSplitterNode::class_name());
    Id id_comb = g.add_node(ImageRGBCombinerNode::class_name());

    auto& in_ports  = g.nodes[id_in]->ports;
    auto& split_ports = g.nodes[id_split]->ports;
    auto& comb_ports = g.nodes[id_comb]->ports;
    auto& out_ports = g.nodes[id_out]->ports;

    Id id_in_port = in_ports.begin()->first;
    Id id_out_port = out_ports.begin()->first;

    Id split_ports_out_id = nullid;
    Id split_ports_in_id = nullid;

    Id split_ports_out_id = nullid;
    Id split_ports_in_id = nullid;

    for (auto& port : split_ports)
    {
        if (port.second->get_direction() == PortDirection::Input)
        {
            split_ports_in_id = port.first;
        }
        else
        {
            split_ports_out_id = port.first;
        }

        if ((split_ports_out_id != nullid) && (split_ports_in_id != nullid))
            break;
    }

    // Connect this three nodes
    assert(g.connect(id_in, id_in_port, id_split, split_ports_in_id) != nullid);
    assert(g.connect(id_split, split_ports_out_id, id_out, id_out_port) != nullid);
    Log::info(g.get_str());

    // remove the spilter node
    assert(g.remove_node(id_split));
    Log::info(g.get_str());

    // connect input and output
    assert(g.connect(id_in, id_in_port, id_out, id_out_port) != nullid);
    Log::info(g.get_str());

    return 0;
}
