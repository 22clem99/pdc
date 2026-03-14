#include "GraphController.hpp"
#include "../../view/dialog/NodePickerDialog/NodePickerDialog.hpp"
#include "../../model/project/node/NodeAllocator.hpp"
#include "cmds/GraphCMD.hpp"
#include <QMessageBox>



GraphController::GraphController(PDCState* model, PDCView* view, QUndoStack* stack) : GenericPDCController(model, view, stack)
{
    Log::debug("Create graph controller");
    connect(view->node_editor->scene, &GraphScene::request_add_node, this, &GraphController::on_open_node_picker);
    connect(this, &GraphController::add_node_to_view, view->node_editor->scene, &GraphScene::add_node_to_graph);
    connect(this, &GraphController::ask_clear_scene, view->node_editor->scene, &GraphScene::clear_scene);
    connect(view->node_editor->scene, &GraphScene::on_node_move, this, &GraphController::on_move_node);
    connect(model->get_project().get(), &Project::node_position_changed, view->node_editor->scene, &GraphScene::update_node_view);
}

GraphController::~GraphController()
{
    emit ask_clear_scene();

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

    for (auto node_type : selected_nodes)
    {
        Log::info("View requested to create nodes: " + node_type);

        auto test_result = model->get_project()->can_add_node(node_type);

        switch (test_result)
        {
        case NodeCreationTestStatus::TypeDoesNotExist:
            QMessageBox::warning(nullptr, "Error", "The view asked for unknow node type");
            return;
        case NodeCreationTestStatus::HeadAlreadyExist:
            QMessageBox::warning(nullptr, "Warning", "Input node already exist can't be instanciate twice");
            return;
        case NodeCreationTestStatus::TailAlreadyExist:
            QMessageBox::warning(nullptr, "Warning", "Output node already exist can't be instanciate twice");
            return;
        case NodeCreationTestStatus::OK:
            Log::debug("Node can be instanciate");
            break;
        default:
            Log::error("Project return an unkwnow code when ask to create a node");
            return;
        }

        // Create the cmd
        auto cmd = new AddNodeCommand(model->get_project()->get_graph_editor(), node_type, scene_pos);
        // push the cmd to the undo stack
        undo_stack->push(cmd);

        // Get the data returned by the add node cmd
        auto data = cmd->data;

        // Generate a signal to the view to print the node
        emit add_node_to_view(data);
    }
}

void GraphController::on_move_node(const Id& id, const QPointF& position)
{
    Log::debug("Node " + id + " position change, update the model");

    undo_stack->push(new MoveNodeCommand(model->get_project()->get_graph_editor(), id, position));
}