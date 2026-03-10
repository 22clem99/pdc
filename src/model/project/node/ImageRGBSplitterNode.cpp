/**
 * @file ImageRGBSplitterNode.cpp
 * @brief Implementation of the ImageRGBSplitterNode class
 */

#include "ImageRGBSplitterNode.hpp"

#include <memory>
#include <functional>

#include <utils/Log.hpp>
#include <utils/Types.hpp>


ImageRGBSplitterNode::ImageRGBSplitterNode()
{
    auto img_input = std::make_unique<Port<Image>>(PortDirection::Input, ConnectionMode::Single);
    auto img_output_R = std::make_unique<Port<Image>>(PortDirection::Output, ConnectionMode::Multiple);
    auto img_output_G = std::make_unique<Port<Image>>(PortDirection::Output, ConnectionMode::Multiple);
    auto img_output_B = std::make_unique<Port<Image>>(PortDirection::Output, ConnectionMode::Multiple);

    ports.emplace(img_input->id, std::move(img_input));
    ports.emplace(img_output_R->id, std::move(img_output_R));
    ports.emplace(img_output_G->id, std::move(img_output_G));
    ports.emplace(img_output_B->id, std::move(img_output_B));
}

ImageRGBSplitterNode::ImageRGBSplitterNode(const nlohmann::json& j)
{

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
    return "This node spit RGB channels into three images\n"
            "(Output_1 = Input[R], Output_2 = Input[G] and Output_3 = Input[B])";
}