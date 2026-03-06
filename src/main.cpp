#include <QApplication>

#include <utils/Log.hpp>
#include "controller/PDCController.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PDCController controller;

    return app.exec();
}