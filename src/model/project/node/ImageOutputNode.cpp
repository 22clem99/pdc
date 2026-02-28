#include "ImageOutputNode.hpp"

#include <utils/Log.hpp>
#include <utils/Types.hpp>

#include <memory>
#include <functional>

ImageOutputNode::ImageOutputNode()
{
    auto img_output = make_unique<Port<Image>>();

    img_output->dir = PortDirection::Input;
    img_output->mode = ConnectionMode::Single;

    ports.emplace(img_output->id, move(img_output));
}


string ImageOutputNode::class_name()
{
    return "ImageOutputNode";
}

NodeKind ImageOutputNode::get_kind()
{
    return kind;
}

string ImageOutputNode::get_str(void)
{
    return get_str(0);
}

string ImageOutputNode::get_str(const unsigned int tab)
{
    return get_str(tab);
}

int ImageOutputNode::compute_output()
{
    return 0;
}