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

    s += get_class_name() +" {\n\tid: \"" + id + "\";\n\tinputs: [\n";

    for (auto const& [key, val] : inputs)
    {
        s += "\t\t [" + key + "]\n";
    }

    s += "\t];\n\toutputs: [\n";

    for (auto const& [key, val] : outputs)
    {
        s += "\t\t [" + key + "]\n";
    }

    s += "\t];\n}";

    return s;
}