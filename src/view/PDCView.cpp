#include "PDCView.hpp"

#include <utils/Log.hpp>

PDCView::PDCView()
{
    set_title("Point De Croix");
    set_default_size(400, 400);

    Log::debug("PDCView created");

    return;
}
