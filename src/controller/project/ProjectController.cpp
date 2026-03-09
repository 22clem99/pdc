#include <QMessageBox>

#include "ProjectController.hpp"
#include "../../view/dialog/NewProjectDialog/NewProjectDialog.hpp"
#include "../../view/dialog/OpenProjectDialog/OpenProjectDialog.hpp"
#include "../../view/PDCMenuBar/PDCMenuBar.hpp"
#include "cmds/ProjectCMD.hpp"

ProjectController::ProjectController(PDCState* model, PDCView* view, QUndoStack* stack) : GenericPDCController(model, view, stack)
{
    connect(view->menu_bar, &PDCMenuBar::new_requested, this, &ProjectController::on_create_project);
    connect(view->menu_bar, &PDCMenuBar::save_requested, this, &ProjectController::on_save_project);
    connect(view->menu_bar, &PDCMenuBar::open_requested, this, &ProjectController::on_open_project);
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

    view->setWindowTitle(QString::fromStdString(name) + " (not saved)");

    connect(model->get_project().get(), &Project::image_changed, view->input_image_view, &ImageView::update_image);

    emit model->get_project()->image_changed(model->get_project()->get_input_image());
}

void ProjectController::on_save_project(void)
{
    Log::debug("Save requested");
    if (model->has_project())
    {
        switch(model->save_project())
        {
        case SaveProjectStatus::FailedToCreateTemp:
            QMessageBox::warning(nullptr, "Error", "Unable to create temporary project file");
            break;
        case SaveProjectStatus::FailedToAddFile:
            QMessageBox::warning(nullptr, "Error", "Unable to write file in project");
            break;
        case SaveProjectStatus::FailedToRenameTemp:
            QMessageBox::warning(nullptr, "Error", "Unable to create final project file");
            break;
        case SaveProjectStatus::Saved:
            view->setWindowTitle(QString::fromStdString(model->get_project()->get_name()));
            break;

        default:
            break;
        }
    }
}

void ProjectController::on_open_project(void)
{
    OpenProjectDialog dialog;

    // Ask the file to open
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

    auto path = dialog.project_path().toStdString();

    Log::debug("Will try to open the file :" + path);

    OpenProjectStatus status = Project::is_project_file_valid(std::filesystem::path(path));

    switch(status)
    {
    case OpenProjectStatus::CantOpenArchive:
        QMessageBox::warning(nullptr, "Error", "Unable to open the project file");
        return;
    case OpenProjectStatus::ManifestNotFound:
        QMessageBox::warning(nullptr, "Error", "Manifest not found in the project");
        return;
    case OpenProjectStatus::ManifestParsingError:
        QMessageBox::warning(nullptr, "Error", "Unable to parse the manifest from the project file");
        return;
    case OpenProjectStatus::ProjectDoesNotExist:
        QMessageBox::warning(nullptr, "Error", "Unable to locate the file");
        return;
    case OpenProjectStatus::Opened:
        break;
    default:
        break;
    }

    Log::debug("Project file:" + path + " is valid, now load it!");

    if(!model->open_project(path))
    {
        QMessageBox::warning(nullptr, "Error", "Something went wrong when the project has been allocate");
        return;
    }

    Log::info("File: " + path + "has been successfully loaded");
    view->setWindowTitle(QString::fromStdString(model->get_project()->get_name()));
}

// void ProjectController::load_image(void)
// {

// }