#include "GraphController.hpp"
#include "../../view/dialog/NodePickerDialog/NodePickerDialog.hpp"
#include "../../model/project/node/NodeAllocator.hpp"
#include "cmds/GraphCMD.hpp"



GraphController::GraphController(PDCState* model, PDCView* view, QUndoStack* stack) : GenericPDCController(model, view, stack)
{
    Log::debug("Create graph controller");
    connect(view->node_editor->scene, &GraphScene::request_add_node, this, &GraphController::on_open_node_picker);
}

GraphController::~GraphController()
{
    Log::debug("Delete graph controller");
    disconnect(this, nullptr, nullptr, nullptr);
    disconnect(nullptr, nullptr, this, nullptr);
}

void GraphController::on_open_node_picker(const QPointF& scene_pos)
{
    Log::info("Ask to add a node");

    NodePickerDialog dialog(NodeAllocator::get_available_node(), nullptr);

    // Then create the view of the NodePicker
    if (dialog.exec() != QDialog::Accepted)
        return;


    auto selected_nodes = dialog.get_selected_node_id();

    for (auto id : selected_nodes)
    {
        Log::info("View requested to create nodes: " + id);
        undo_stack->push(new AddNodeCommand(model->get_project()->get_graph_editor(), id, scene_pos));
    }
}