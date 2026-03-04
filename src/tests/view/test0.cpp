#include <QApplication>
#include "../../view/PDCView.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    PDCView window;
    window.show();

    return app.exec();
}