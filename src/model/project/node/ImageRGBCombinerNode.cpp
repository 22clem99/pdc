/**
 * @file ImageRGBCombinerNode.cpp
 * @brief Implementation of the ImageRGBCombinerNode class
 */

#include "ImageRGBCombinerNode.hpp"

#include <memory>
#include <functional>

#include <utils/Log.hpp>
#include <utils/Types.hpp>
#include <json/json.hpp>
#include "utils/JSONWrapper.hpp"

const std::vector<PortDef> ImageRGBCombinerNode::port_defs = {
    NODE_PORT("output", Image, PortDirection::Output, ConnectionMode::Multiple),
    NODE_PORT("R_input", Image, PortDirection::Input, ConnectionMode::Single),
    NODE_PORT("G_input", Image, PortDirection::Input, ConnectionMode::Single),
    NODE_PORT("B_input", Image, PortDirection::Input, ConnectionMode::Single)
};

ImageRGBCombinerNode::ImageRGBCombinerNode() : Node(port_defs)
{
    // Nothing to do here
}

ImageRGBCombinerNode::ImageRGBCombinerNode(const nlohmann::json& j) : Node(j, port_defs)
{
    // Nothing to do here
}

std::string ImageRGBCombinerNode::class_name()
{
    return "ImageRGBCombinerNode";
}

NodeKind ImageRGBCombinerNode::get_kind()
{
    return kind;
}

std::string ImageRGBCombinerNode::get_str(void)
{
    return get_str(0);
}

std::string ImageRGBCombinerNode::get_str(const unsigned int tab)
{
    return get_str(tab);
}

int ImageRGBCombinerNode::compute_output()
{
    return 0;
}

std::string ImageRGBCombinerNode::get_pretty_print(void)
{
    return "Image RGB combiner";
}

std::string ImageRGBCombinerNode::get_description(void)
{
    return "This node combine channel RGB of three node to create a new image"
            "(Output = Input_1[R] + Input_2[G]+ Input_3[B])";
}

bool ImageRGBCombinerNode::is_json_valid(const nlohmann::json& j)
{
    return Node::is_json_valid(j, port_defs);
}