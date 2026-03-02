/**
 * @file Node.cpp
 * @brief Implementation of the Base class Node
 */

#include "Node.hpp"
#include <utils/Tab.hpp>

std::string Node::class_name()
{
    return "Node";
}

std::string Node::get_str()
{
    return get_str(0);
}

std::string Node::get_str(const unsigned int tab)
{
    std::string s = "";
    std::string s_tab = Tab::tab(tab);

    s += s_tab + get_class_name() +" {\n"
        + s_tab + "\tid: \"" + id + "\";\n"
        + s_tab + "\tports: [\n";

    for (auto port = ports.begin(); port != ports.end(); port++)
    {
        s += "\t" + port->second->get_str(tab + 1) + "\n";
    }

    s += s_tab +"\t];\n"
        + s_tab + "}";

    return s;
}