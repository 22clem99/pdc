/**
 * @file ImageRGBCombinerNode.cpp
 * @brief Implementation of the ImageRGBCombinerNode class
 */

#include "ImageRGBCombinerNode.hpp"

#include <memory>
#include <functional>

#include <utils/Log.hpp>
#include <utils/Types.hpp>


ImageRGBCombinerNode::ImageRGBCombinerNode()
{
    auto img_output = std::make_unique<Port<Image>>(PortDirection::Output, ConnectionMode::Multiple);
    auto img_input_R = std::make_unique<Port<Image>>(PortDirection::Input, ConnectionMode::Single);
    auto img_input_G = std::make_unique<Port<Image>>(PortDirection::Input, ConnectionMode::Single);
    auto img_input_B = std::make_unique<Port<Image>>(PortDirection::Input, ConnectionMode::Single);

    ports.emplace(img_output->id, std::move(img_output));
    ports.emplace(img_input_R->id, std::move(img_input_R));
    ports.emplace(img_input_G->id, std::move(img_input_G));
    ports.emplace(img_input_B->id, std::move(img_input_B));
}

ImageRGBCombinerNode::ImageRGBCombinerNode(const nlohmann::json& j)
{

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