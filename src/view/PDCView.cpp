#include "PDCView.hpp"

#include <iostream>

PDCView::PDCView()
{
    set_title("Point De Croix");
    set_default_size(400, 400);

    std::cout << "PDCView created" << std::endl;

    return;
}
