#include "Image.hpp"
#include <utils/Tab.hpp>

std::string Image::class_name(void)
{
    return "Image";
}

std::string Image::get_str(void) const
{
    return get_str(0);
}

std::string Image::get_str(const unsigned int tab) const
{
    return Tab::tab(tab) + "Image, value=TODO";
}
