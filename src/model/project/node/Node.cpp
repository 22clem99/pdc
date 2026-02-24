#include "Node.hpp"

string Node::class_name()
{
    return "Node";
}

int Node::add_input(InputVariant& in)
{
    // if (inputs.contains(in.id)) {
    return 0;
    // }
}

int Node::add_output(OutputVariant &out)
{
    // if (inputs.contains(in.id)) {
    return 0;
    // }
}

string Node::get_str(void)
{
    string s = "";

    s += "Node {\n\tid: \n\"" + id + "\"\n\tinputs: [\n";
    // TODO, print dict of inputs
    s += "\t]\n\toutputs: [\n";
    // TODO, print dict of outputs
    s += "}\n";

    return s;
}