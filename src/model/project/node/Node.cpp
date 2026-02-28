#include "Node.hpp"
#include <utils/Tab.hpp>

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

string Node::get_str()
{
    return get_str(0);
}

string Node::get_str(const unsigned int tab)
{
    string s = "";
    string s_tab = Tab::tab(tab);

    s += s_tab + get_class_name() +" {\n"
        + s_tab + "\tid: \"" + id + "\";\n"
        + s_tab + "\tports: [\n";

    for (auto port = ports.begin(); port != ports.end(); port++)
    {
        std::visit([&](auto& ptr) {
            s += "\t" + ptr->get_str(tab + 1) + "\n";
        }, port->second);
    }

    s += s_tab +"\t];\n"
        + s_tab + "}";

    return s;
}