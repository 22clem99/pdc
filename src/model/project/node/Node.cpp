/**
 * @file Node.cpp
 * @brief Implementation of the Base class Node
 */

#include "Node.hpp"
#include <utils/Tab.hpp>
#include "utils/JSONWrapper.hpp"
#include <QString>

Node::Node(const std::vector<PortDef> ports_def, QObject* parent) : QObject(parent)
{
    for (const auto& def : ports_def)
    {
        auto port = def.creator();

        ports.emplace(port->get_id(), std::move(port));
    }
}

Node::Node(const nlohmann::json& j, const std::vector<PortDef> ports_def, QObject* parent) : QObject(parent)
{
    Log::debug(" Will tried to decode json: \n" + j.dump(4));

    id = j["id"];

    for (auto port : j["ports"])
    {
        for (const auto& def : ports_def)
        {
            if (port["alias"] == def.alias)
            {
                auto new_port = def.creator();

                new_port->set_id(port["id"]);

                ports.emplace(new_port->get_id(), std::move(new_port));
            }
        }
    }


    position.setX(0);
    if (j.contains("x_pos"))
    {
        if (j["x_pos"].is_number_float())
        {
            position.setX(j["y_pos"].get<double>());
        }
    }

    position.setY(0);
    if (j.contains("y_pos"))
    {
        if( j["y_pos"].is_number_float())
        {
            position.setY(j["y_pos"].get<double>());
        }
    }
}

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

    return {{"id", id}, {"node_type", get_class_name()}, {"ports", ports_array}, {"x_pos", position.x()}, {"y_pos", position.y()}};
}

std::string node_kind_to_str(NodeKind kind)
{
    switch (kind)
    {
    case NodeKind::Head:
        return "Input";
    case NodeKind::Tail:
        return "Output";
    case NodeKind::Regular:
        return "Regular";
    default:
        break;
    }
    return "";
}

bool Node::is_json_valid(const nlohmann::json& j, const std::vector<PortDef> ports_def)
{
    if (!j.is_object())
    {
        return false;
    }

    // No need to check for "id", "node_type" and "ports" as it is already done
    // from the method caller. We just need to check port(s)

    std::set<std::string> json_alias;

    // Iterate on each node and create a list of all alias used
    for (const auto& port : j["ports"])
    {
        JSON_REQUIRED_FIELD(port, "id", is_string);
        JSON_REQUIRED_FIELD(port, "alias", is_string);

        Log::debug("Json parsing: port id and alias are there, continue with the alias analyse");

        json_alias.insert(port["alias"]);

        Log::debug("Json parsing: Add alias: " + port["alias"].dump() + " in list");
    }

    // Review all aliases to check thez are all used
    for (auto& def : ports_def)
    {
        if (!json_alias.contains(def.alias))
        {
            Log::debug("Json parsing: alias: " + def.alias + "in not in the list");
            return false;
        }
    }
    return true;
}

void Node::set_position(const QPointF& pos)
{
    position = pos;

    if(notifier)
    {
        notifier->node_position_changed(id, pos);
    }
}

QPointF Node::get_position(void)
{
    return position;
}

void Node::set_notifier(NodeNotifier* n)
{
    notifier = n;
}


NodeNotifier* Node::get_notifier(void)
{
    return notifier;
}

std::vector<PortData> Node::get_ports_data(PortDirection dir)
{
    std::vector<PortData> data;

    for (auto& [id, port] : ports)
    {
        if ((dir == port->get_direction()) && (ConnectionMode::None != port->get_connection_mode()))
        {
            data.push_back(PortData{id,
                            port->get_port_type()});
        }
    }

    return data;
}