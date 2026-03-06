#ifndef PDC_CONTROLLER_H
#define PDC_CONTROLLER_H

#include <QUndoStack>

#include "../view/PDCView.hpp"
#include "../model/PDCState.hpp"
#include "project/ProjectController.hpp"


class PDCController
{
public:
    PDCState model;
    PDCView view;

    QUndoStack undo_stack;

    // Sub controller
    ProjectController project_controller;

    PDCController() : project_controller(&model, &view, &undo_stack)
    {
        view.show();
    }
};


#endif