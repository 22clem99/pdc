#include "Node.hpp"

string Node::class_name()
{
    return "Node";
}

int Node::add_port(PortVariant& p)
{
    // if (inputs.contains(in.id)) {
    return 0;
    // }
}

string Node::get_str(void)
{
    string s = "";

    s += get_class_name() +" {\n\tid: \"" + id + "\";\n\tports: [\n";

    for (auto const& [key, val] : ports)
    {
        s += "\t\t [" + key + "]\n";
    }

    s += "\t];\n}";

    return s;
}