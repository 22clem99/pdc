#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H

#include "GenericPDCController.hpp"
#include "../../view/PDCView.hpp"
#include "../../model/PDCState.hpp"


class ProjectController : public GenericPDCController
{
    Q_OBJECT

public:
    ProjectController(PDCState* model, PDCView* view, QUndoStack* stack);

    void on_create_project(void);
    void on_save_project(void);
};


#endif