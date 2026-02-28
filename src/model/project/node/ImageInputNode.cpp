#include "ImageInputNode.hpp"

#include <utils/Log.hpp>
#include <utils/Types.hpp>

#include <memory>
#include <functional>

ImageInputNode::ImageInputNode()
{
    auto img_output = make_unique<Port<Image>>();

    img_output->dir = PortDirection::Output;
    img_output->mode = ConnectionMode::Multiple;

    ports.emplace(img_output->id, move(img_output));
}


string ImageInputNode::class_name()
{
    return "ImageInputNode";
}

NodeKind ImageInputNode::get_kind()
{
    return kind;
}

string ImageInputNode::get_str(void)
{
    return get_str(0);
}

string ImageInputNode::get_str(const unsigned int tab)
{
    return get_str(tab);
}

int ImageInputNode::compute_output()
{
    return 0;
}