#include <QMessageBox>

#include "ProjectController.hpp"
#include "../../view/dialog/NewProjectDialog/NewProjectDialog.hpp"
#include "../../view/dialog/OpenProjectDialog/OpenProjectDialog.hpp"
#include "../../view/dialog/YesNoDialog/YesNoDialog.hpp"
#include "../../view/PDCMenuBar/PDCMenuBar.hpp"
#include "cmds/ProjectCMD.hpp"

ProjectController::ProjectController(PDCState* model, PDCView* view, QUndoStack* stack) : GenericPDCController(model, view, stack)
{
    connect(view->menu_bar, &PDCMenuBar::new_requested, this, &ProjectController::on_create_project);
    connect(view->menu_bar, &PDCMenuBar::save_requested, this, &ProjectController::on_save_project);
    connect(view->menu_bar, &PDCMenuBar::open_requested, this, &ProjectController::on_open_project);
    connect(view->menu_bar, &PDCMenuBar::close_requested, this, &ProjectController::on_close_project);
}

void ProjectController::on_create_project(void)
{
    NewProjectDialog dialog;

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

    on_close_project();

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
    else
    {
        Log::info("Nothing to save");
    }
}

void ProjectController::on_open_project(void)
{
    OpenProjectDialog dialog;


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

    on_close_project();

    if(!model->open_project(path))
    {
        QMessageBox::warning(nullptr, "Error", "Something went wrong when the project has been allocate");
        return;
    }

    Log::info("File: " + path + " has been successfully loaded");
    view->setWindowTitle(QString::fromStdString(model->get_project()->get_name()));

    connect(model->get_project().get(), &Project::image_changed, view->input_image_view, &ImageView::update_image);

    emit model->get_project()->image_changed(model->get_project()->get_input_image());
}

void ProjectController::on_close_project(void)
{
    // Ask the file to open
    if (model->has_project())
    {
        if (model->get_project()->is_dirty())
        {
            YesNoDialog yes_no_dialog(nullptr, "Do you want to save the project before to close it");

            if (yes_no_dialog.exec() == QDialog::Accepted)
            {
                ProjectController::on_save_project();
            }
            else
            {
                Log::info("All modifications will be discard");
            }
        }
    }
    else
    {
        Log::info("Nothing to close");
        return;
    }

    // First remove connection
    // TODO disconnect()
    disconnect(model->get_project().get(), nullptr, nullptr, nullptr);
    disconnect(nullptr, nullptr, model->get_project().get(), nullptr);

    // Then remove Project
    model->close_project();

    // Clear all visual artefact
    view->input_image_view->clear_view();
    view->output_image_view->clear_view();

    // Clear title
    view->setWindowTitle(QString::fromStdString(""));

}