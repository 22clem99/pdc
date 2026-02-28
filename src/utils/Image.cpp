#include "Image.hpp"
#include <utils/Tab.hpp>

string Image::class_name(void)
{
    return "Image";
}

string Image::get_str(void)
{
    return get_str(0);
}

string Image::get_str(const unsigned int tab)
{
    return Tab::tab(tab) + "Image, value=TODO";
}
