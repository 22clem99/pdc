#include "view/PDCView.hpp"

#include <iostream>
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
    // TODO: Implement here PointDeCroix
    std::cout << "Work in progress" << std::endl;

    auto app = Gtk::Application::create("point.de.croix");

    //Shows the window and returns when it is closed.
    return app->make_window_and_run<PDCView>(argc, argv);
}
