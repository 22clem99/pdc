#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H

#include "GenericPDCController.hpp"
#include "../../view/PDCView.hpp"
#include "../../model/PDCState.hpp"
#include "GraphController.hpp"


class ProjectController : public GenericPDCController
{
    Q_OBJECT

public:
    ProjectController(PDCState* model, PDCView* view, QUndoStack* stack, QObject* parent = nullptr);

    void on_create_project(void);
    void on_save_project(void);
    void on_open_project(void);
    void on_close_project(void);
    void on_export_project(void);
    bool on_close_window(void);

    GraphController* graph_con;
    PDCView* view;
    PDCState* model;
};


#endif