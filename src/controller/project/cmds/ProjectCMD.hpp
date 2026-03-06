#ifndef PROJECT_CMD_H
#define PROJECT_CMD_H

#include <QUndoCommand>
#include <string>

#include "../../../model/PDCState.hpp"

class CreateProjectCommand : public QUndoCommand
{
public:
    CreateProjectCommand(PDCState* model, const std::string& prj_name,  const std::string& prj_path, const std::string& img_path)
        : model(model), name(prj_name), path(prj_path), img_path(img_path)
    {
        setText("Create Project");
    }

    void undo() override
    {
    }

    void redo() override
    {
        model->create_project(name, path, img_path);
    }

private:
    PDCState* model;
    std::string name;
    std::string path;
    std::string img_path;
};

#endif