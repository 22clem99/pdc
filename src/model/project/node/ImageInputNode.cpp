/**
 * @file ImageInputNode.cpp
 * @brief Implementing the ImageInputNode class
 */

#include "ImageInputNode.hpp"

#include <memory>
#include <functional>

#include <utils/Log.hpp>
#include <utils/Types.hpp>
#include <json/json.hpp>
#include "utils/JSONWrapper.hpp"

const std::vector<PortDef> ImageInputNode::port_defs = {
    NODE_PORT("output", Image, PortDirection::Output, ConnectionMode::Multiple)
};

ImageInputNode::ImageInputNode(QObject* parent) : Node(port_defs, parent)
{
    // Nothing to do here
}

ImageInputNode::ImageInputNode(const nlohmann::json& j, QObject* parent) : Node(j, port_defs, parent)
{
    // Nothing to do here
}

std::string ImageInputNode::class_name()
{
    return "ImageInputNode";
}

NodeKind ImageInputNode::get_kind()
{
    return kind;
}

std::string ImageInputNode::get_str(void)
{
    return get_str(0);
}

std::string ImageInputNode::get_str(const unsigned int tab)
{
    return get_str(tab);
}

int ImageInputNode::compute_output()
{
    return 0;
}
std::string ImageInputNode::get_pretty_print(void)
{
    return "Image input";
}

std::string ImageInputNode::get_description(void)
{
    return "This node is a simple input node, it is the node used to inject in the PDC project";
}

bool ImageInputNode::is_json_valid(const nlohmann::json& j)
{
    return Node::is_json_valid(j, port_defs);
}