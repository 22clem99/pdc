/**
 * @file ImageOutputNode.cpp
 * @brief Implementation of the ImageOutputNode class
 */

#include "ImageOutputNode.hpp"

#include <memory>
#include <functional>

#include <utils/Log.hpp>
#include <utils/Types.hpp>
#include <json/json.hpp>
#include "utils/JSONWrapper.hpp"

const std::vector<PortDef> ImageOutputNode::port_defs = {
    NODE_PORT("input", Image, PortDirection::Input, ConnectionMode::Single)
};

ImageOutputNode::ImageOutputNode(QObject* parent) : Node(port_defs, parent)
{
    // Nothing to do here
}

ImageOutputNode::ImageOutputNode(const nlohmann::json& j, QObject* parent) : Node(j, port_defs, parent)
{
    // Nothing to do here
}

std::string ImageOutputNode::class_name()
{
    return "ImageOutputNode";
}

NodeKind ImageOutputNode::get_kind()
{
    return kind;
}

std::string ImageOutputNode::get_str(void)
{
    return get_str(0);
}

std::string ImageOutputNode::get_str(const unsigned int tab)
{
    return get_str(tab);
}

int ImageOutputNode::compute_output()
{
    return 0;
}

std::string ImageOutputNode::get_pretty_print(void)
{
    return "Image output";
}

std::string ImageOutputNode::get_description(void)
{
    return "This node is a simple output node, it is the node used to export the PDC project";
}

bool ImageOutputNode::is_json_valid(const nlohmann::json& j)
{
    return Node::is_json_valid(j, port_defs);
}