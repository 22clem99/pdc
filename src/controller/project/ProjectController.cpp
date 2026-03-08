#include <QMessageBox>

#include "ProjectController.hpp"
#include "../../view/dialog/NewProjectDialog/NewProjectDialog.hpp"
#include "../../view/PDCMenuBar/PDCMenuBar.hpp"
#include "cmds/ProjectCMD.hpp"

ProjectController::ProjectController(PDCState* model, PDCView* view, QUndoStack* stack) : GenericPDCController(model, view, stack)
{
    connect(view->menu_bar, &PDCMenuBar::new_requested, this, &ProjectController::on_create_project);
    connect(view->menu_bar, &PDCMenuBar::save_requested, this, &ProjectController::on_save_project);
}

void ProjectController::on_create_project(void)
{
    NewProjectDialog dialog;

    if (model->has_project())
    {
        if (model->get_project()->is_dirty())
        {
            QMessageBox::warning(nullptr, "Error", "Save the project before to open a new one");
            return;
        }
    }

    if (dialog.exec() != QDialog::Accepted)
        return;

    auto name = dialog.project_name().toStdString();
    auto prj_path = dialog.project_path().toStdString() + std::filesystem::path::preferred_separator + name + Project::get_extension();
    auto img_path = dialog.image_path().toStdString();

    CreateProjectStatus create_status = model->can_create_project(prj_path, img_path);

    if (create_status == CreateProjectStatus::ImageDoNotExist)
    {
        QMessageBox::warning(nullptr, "Error", "Image does not exist");
        return;
    }
    else if (create_status == CreateProjectStatus::ProjectPathAlreadyExist)
    {
        QMessageBox::warning(nullptr, "Error", "Project already exists");
        return;
    }

    undo_stack.push(new CreateProjectCommand(model, name, prj_path, img_path));

    // Update title of the mainwindow :
    // auto window_name = new QString(name);

    view->setWindowTitle(QString::fromStdString(name) + " (not saved)");
}

void ProjectController::on_save_project(void)
{
    Log::debug("Save requested");
    if (model->has_project())
    {
        switch(model->save_project())
        {
        case SaveProjectStatus::FAILED_TO_CREATE_TEMP:
            QMessageBox::warning(nullptr, "Error", "Unable to create temporary project file");
            break;
        case SaveProjectStatus::FAILED_TO_ADD_FILE:
            QMessageBox::warning(nullptr, "Error", "Unable to write file in project");
            break;
        case SaveProjectStatus::FAILED_TO_RENAME_TEMP:
            QMessageBox::warning(nullptr, "Error", "Unable to create final project file");
            break;
        case SaveProjectStatus::SAVED:
            view->setWindowTitle(QString::fromStdString(model->get_project()->get_name()));
            break;

        default:
            break;
        }
    }
}