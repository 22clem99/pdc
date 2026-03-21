#include <QMessageBox>

#include "GraphController.hpp"
#include "../../view/dialog/NodePickerDialog/NodePickerDialog.hpp"
#include "../../model/project/node/NodeAllocator.hpp"
#include "cmds/GraphCMD.hpp"



GraphController::GraphController(GraphEditor* model, GraphViewer* view, QUndoStack* stack, QObject* parent) : editor(model), view(view), GenericPDCController(stack, parent)
{
    Log::debug("Create graph controller");
    connect(view->scene, &GraphScene::request_add_node, this, &GraphController::on_open_node_picker);
    connect(view->scene, &GraphScene::on_node_move, this, &GraphController::on_move_node);
    connect(view->scene, &GraphScene::request_remove_node, this, &GraphController::on_request_remove_node);
    connect(this, &GraphController::ask_clear_scene, view->scene, &GraphScene::clear_scene);
    connect(view->scene, &GraphScene::request_new_edge, this, &GraphController::on_request_create_edge);

    // Connect event from the node editor to the view
    connect(editor, &GraphEditor::node_has_been_added, view->scene, &GraphScene::add_node_to_graph);
    connect(editor, &GraphEditor::node_has_been_delete, view->scene, &GraphScene::remove_node_to_graph);
    connect(editor, &GraphEditor::node_position_changed, view->scene, &GraphScene::update_node_view);

    // Update the view there
    sync_view_model();
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

        auto test_result = editor->can_add_node(node_type);

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
            Log::error("Node editor return an unknown code when ask to create a node");
            return;
        }

        // Create the cmd
        auto cmd = new AddNodeCommand(editor, node_type, scene_pos);
        // push the cmd to the undo stack
        undo_stack->push(cmd);
    }
}

void GraphController::on_move_node(const Id& id, const QPointF& position)
{
    Log::debug("Node " + id + " position change, update the model");

    undo_stack->push(new MoveNodeCommand(editor, id, position));
}

void GraphController::sync_view_model(void)
{
    view->scene->clear_scene();

    // Ask to the model the graph
    auto nodes_data = editor->get_nodes_data();

    for (auto data : nodes_data)
    {
        view->scene->add_node_to_graph(data);
    }

    // Add here edges
}

void GraphController::on_request_remove_node(const Id& id)
{
    Log::debug("View request to remove the node " + id);

    undo_stack->push(new RemoveNodeCommand(editor, id));
}

void GraphController::on_request_create_edge(const Id& from_node, const Id& from_port, const Id& to_node, const Id& to_port)
{
    Log::debug("View request to create an edge from [" + from_port + "](" + from_node + ") et [" + to_port + "](" + to_node + ")");

    Id src_node, src_port, dst_node, dst_port;

    // First check which port is the ouput, from the view
    // point, an edge is not oriented. We need to check at
    // this level to link an output and an input.
    if (editor->is_output(from_node, from_port) && editor->is_input(to_node, to_port))
    {
        // Data was sent in the good order
        Log::debug("View ask to create the edge with data in good order");

        src_node = from_node;
        src_port = from_port;
        dst_node = to_node;
        dst_port = to_port;
    }
    else if (editor->is_input(from_node, from_port) && editor->is_output(to_node, to_port))
    {
        // Data was sent in the wrong order, but we will create the edge anyway
        Log::debug("View ask to create the edge with data in bad order");

        src_node = to_node;
        src_port = to_port;
        dst_node = from_node;
        dst_port = from_port;
    }
    else
    {
        Log::info("Trying to link an input to an input, or an output to an output.");
        return;
    }

    // Test that we can create the new edge
    auto test_result = editor->can_add_edge(src_node, src_port, dst_node, dst_port);

    switch (test_result)
    {
    case EdgeCreationTestStatus::DestNodeDoesNotExist:
    case EdgeCreationTestStatus::SrcNodeDoesNotExist:
        QMessageBox::warning(nullptr, "Error", "The view asked to link nodes with an unknow node");
        return;
    case EdgeCreationTestStatus::DestPortDoesNotExist:
    case EdgeCreationTestStatus::SrcPortDoesNotExist:
        QMessageBox::warning(nullptr, "Error", "The view asked to link nodes with an unknow port");
        return;
    case EdgeCreationTestStatus::PortAreNotTheSameType:
        QMessageBox::warning(nullptr, "Warning", "Can't link two different data port");
        return;
    case EdgeCreationTestStatus::SrcConnectionTypeIsWrong:
        QMessageBox::warning(nullptr, "Error", "The output can't be linked");
        return;
    case EdgeCreationTestStatus::DestNotAvailableOrNotSingle:
        QMessageBox::warning(nullptr, "Warning", "The input can only linked once");
        return;
    case EdgeCreationTestStatus::OK:
        Log::debug("Edge can be instanciate");
        break;
    default:
        Log::error("Node editor return an unkwnow code when ask to create a node");
        QMessageBox::warning(nullptr, "Error", "Node editor return an unkwnow code when ask to create an edge");
        return;
    }

    // Then ask trought the undo stack to connect the edge
    auto cmd = new AddEdgeCommand(editor, src_node, src_port, dst_node, dst_port);
    // push the cmd to the undo stack
    undo_stack->push(cmd);
}