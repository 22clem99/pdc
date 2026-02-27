#include "ImageInputNode.hpp"

#include <utils/Log.hpp>
#include <utils/Types.hpp>

#include <memory>
#include <functional>

ImageInputNode::ImageInputNode()
{
    auto img_output = make_unique<Output<Image>>();
    outputs.emplace(img_output->id, move(img_output));
}


string ImageInputNode::class_name()
{
    return "ImageInputNode";
}

string ImageInputNode::get_str(void)
{
    return get_str();
}

int ImageInputNode::compute_output()
{
    return 0;
}