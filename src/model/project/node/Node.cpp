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

void Node::set_visit_status(VisitState state)
{
    visite_state = state;
}

VisitState Node::get_visit_status(void)
{
    return visite_state;
}

void Node::clear_visit_status(void)
{
    visite_state = VisitState::NotVisited;
}

std::vector<Id> Node::get_ports_from_direction(PortDirection dir)
{
    std::vector<Id> ports_dir = {};
    for (auto& port : ports)
    {
        if (port.second->get_direction() == dir)
        {
            ports_dir.push_back(port.first);
        }
    }

    return (ports_dir);
}

nlohmann::json Node::to_json(void)
{
    using nlohmann::json;

    json ports_array = json::array();

    for (auto& port : ports)
    {
        ports_array.push_back(port.second->to_json());
    }

    return {{"id", id}, {"node_type", class_name()}, {"ports", ports_array}};
}