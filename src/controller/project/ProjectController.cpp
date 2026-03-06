#include <QMessageBox>

#include "ProjectController.hpp"
#include "../../view/dialog/NewProjectDialog/NewProjectDialog.hpp"
#include "../../view/PDCMenuBar/PDCMenuBar.hpp"
#include "cmds/ProjectCMD.hpp"

ProjectController::ProjectController(PDCState* model, PDCView* view, QUndoStack* stack) : GenericPDCController(model, view, stack)
{
    connect(view->menu_bar, &PDCMenuBar::new_requested, this, &ProjectController::on_create_project);
}

void ProjectController::on_create_project(void)
{
    NewProjectDialog dialog;

    if (dialog.exec() != QDialog::Accepted)
        return;

    auto name = dialog.project_name().toStdString();
    auto prj_path = dialog.project_path().toStdString();
    auto img_path = dialog.image_path().toStdString();

    if (!model->can_create_project(prj_path, img_path))
    {
        QMessageBox::warning(nullptr, "Error",
                             "Project already exists");
        return;
    }

    undo_stack.push(new CreateProjectCommand(model, name, prj_path, img_path));
}