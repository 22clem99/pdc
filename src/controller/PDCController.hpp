#ifndef PDC_CONTROLLER_H
#define PDC_CONTROLLER_H

#include <QUndoStack>

#include "../view/PDCView.hpp"
#include "../model/PDCState.hpp"
#include "project/ProjectController.hpp"


class PDCController
{
public:
    PDCState* model;
    PDCView* view;
    QUndoStack* undo_stack;

    // Sub controller
    ProjectController* project_controller;

    PDCController()
    {
        undo_stack = new QUndoStack();
        view = new PDCView(undo_stack);
        model = new PDCState();
        project_controller = new ProjectController(model, view, undo_stack);

        view->show();
    }

    ~PDCController()
    {
        delete project_controller;
        delete model;
        delete view;
        delete undo_stack;
    }
};


#endif