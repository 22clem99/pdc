#include <QApplication>
#include "../../view/PDCView.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QUndoStack stack;


    PDCView window(&stack);
    window.show();

    return app.exec();
}