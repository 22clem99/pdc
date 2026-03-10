/**
 * @file ImageInputNode.cpp
 * @brief Implementing the ImageInputNode class
 */

#include "ImageInputNode.hpp"

#include <memory>
#include <functional>

#include <utils/Log.hpp>
#include <utils/Types.hpp>

ImageInputNode::ImageInputNode()
{
    auto img_output = std::make_unique<Port<Image>>(PortDirection::Output, ConnectionMode::Multiple);

    ports.emplace(img_output->id, std::move(img_output));
}

ImageInputNode::ImageInputNode(const nlohmann::json& j)
{
    //TODO
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
    return "Image input node";
}

std::string ImageInputNode::get_description(void)
{
    return "This node is a simple input node, it is the node used to inject in the PDC project";
}
