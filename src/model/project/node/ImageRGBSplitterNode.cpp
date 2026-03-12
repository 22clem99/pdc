/**
 * @file ImageRGBSplitterNode.cpp
 * @brief Implementation of the ImageRGBSplitterNode class
 */

#include "ImageRGBSplitterNode.hpp"

#include <memory>
#include <functional>

#include <utils/Log.hpp>
#include <utils/Types.hpp>
#include <json/json.hpp>
#include "utils/JSONWrapper.hpp"

const std::vector<PortDef> ImageRGBSplitterNode::port_defs = {
    NODE_PORT("input", Image, PortDirection::Input, ConnectionMode::Single),
    NODE_PORT("R_output", Image, PortDirection::Output, ConnectionMode::Multiple),
    NODE_PORT("G_output", Image, PortDirection::Output, ConnectionMode::Multiple),
    NODE_PORT("B_output", Image, PortDirection::Output, ConnectionMode::Multiple)
};

ImageRGBSplitterNode::ImageRGBSplitterNode() : Node(port_defs)
{
    // Nothing to do here
}

ImageRGBSplitterNode::ImageRGBSplitterNode(const nlohmann::json& j) : Node(j, port_defs)
{
    // Nothing to do here
}


std::string ImageRGBSplitterNode::class_name()
{
    return "ImageRGBSplitterNode";
}

NodeKind ImageRGBSplitterNode::get_kind()
{
    return kind;
}

std::string ImageRGBSplitterNode::get_str(void)
{
    return get_str(0);
}

std::string ImageRGBSplitterNode::get_str(const unsigned int tab)
{
    return get_str(tab);
}

int ImageRGBSplitterNode::compute_output()
{
    return 0;
}

std::string ImageRGBSplitterNode::get_pretty_print(void)
{
    return "Image RGB spitter node";
}

std::string ImageRGBSplitterNode::get_description(void)
{
    return "This node spit RGB channels into three images"
            "(Output_1 = Input[R], Output_2 = Input[G] and Output_3 = Input[B])";
}

bool ImageRGBSplitterNode::is_json_valid(const nlohmann::json& j)
{
    return Node::is_json_valid(j, port_defs);
}