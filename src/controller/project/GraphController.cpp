#include "GraphController.hpp"


GraphController::GraphController(PDCState* model, PDCView* view, QUndoStack* stack) : GenericPDCController(model, view, stack)
{
    connect(view->node_editor->scene, &GraphScene::request_add_node, this, &GraphController::on_open_node_picker);
}

void GraphController::on_open_node_picker(void)
{

}