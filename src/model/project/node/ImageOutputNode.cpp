/**
 * @file ImageOutputNode.cpp
 * @brief Implementation of the ImageOutputNode class
 */

#include "ImageOutputNode.hpp"

#include <memory>
#include <functional>

#include <utils/Log.hpp>
#include <utils/Types.hpp>


ImageOutputNode::ImageOutputNode()
{
    auto img_output = std::make_unique<Port<Image>>(PortDirection::Input, ConnectionMode::Single);

    ports.emplace(img_output->id, std::move(img_output));
}

ImageOutputNode::ImageOutputNode(const nlohmann::json& j)
{

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