/**
 * @file PDCState.hpp
 * @brief This class represent the Model part of a MVC architecture used in this project
 */

#ifndef PDCSTATE_H
#define PDCSTATE_H

#include <memory>

#include "project/Project.hpp"

enum class PDCProjectState
{
    NoProject,
    ProjectOpened
};

enum class CreateProjectStatus
{
    Valid,
    ProjectPathAlreadyExist,
    ImageDoNotExist
};

/**
 * @brief PDCState class is the Model representation of MVC in this project
 *
 */
class PDCState {
private:
    std::unique_ptr<Project> project;
    PDCProjectState state;

public:
    PDCState();

    bool create_project(const std::string& prj_name, const std::string& prj_path, const std::string& img_path);

    bool close_project();

    SaveProjectStatus save_project();

    bool rename_project(const std::string& prj_name);

    CreateProjectStatus can_create_project(const std::string& prj_path, const std::string& img_path);

    bool has_project();

    std::unique_ptr<Project>& get_project();
};

#endif