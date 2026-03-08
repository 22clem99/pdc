/**
 * @file PDCState.cpp
 * @brief Implementation of the PDCState class
 */

#include <fstream>
#include <filesystem>
#include <memory>

#include "PDCState.hpp"
#include "project/Project.hpp"
#include <utils/Log.hpp>

PDCState::PDCState()
{
    state = PDCProjectState::NoProject;
}

bool PDCState::create_project(const std::string& prj_name, const std::string& prj_path, const std::string& img_path)
{
    namespace fs = std::filesystem;

    if(can_create_project(prj_path, img_path) != CreateProjectStatus::Valid)
        return false;

    fs::path folder = fs::path(prj_path);
    fs::path img_path_to_copy = fs::path(img_path);

    // First alocate the project
    project = std::make_unique<Project>(prj_name, prj_path, img_path);
    state = PDCProjectState::ProjectOpened;

    if(project == nullptr)
    {
        Log::error("Unable to allocate project object");
        return false;
    }

    return true;
}

bool PDCState::close_project()
{
    return false;
}

SaveProjectStatus PDCState::save_project()
{
    return project->save();
}

bool PDCState::rename_project(const std::string& prj_name)
{
    return false;
}

CreateProjectStatus PDCState::can_create_project(const std::string& prj_path, const std::string& img_path)
{
    namespace fs = std::filesystem;

    // First test the project path
    std::filesystem::path path_to_test = std::filesystem::path(prj_path);

    if (fs::exists(path_to_test))
        return CreateProjectStatus::ProjectPathAlreadyExist;

    // Then test the image path
    std::filesystem::path img_to_test = std::filesystem::path(img_path);

    if (!fs::exists(img_to_test))
        return CreateProjectStatus::ImageDoNotExist;

    Log::debug("Can create project with: prj_path:\"" + prj_path + "\" and img_path: \"" + img_path + "\"");

    return CreateProjectStatus::Valid;
}

bool PDCState::has_project()
{
    return (state == PDCProjectState::ProjectOpened ? true : false);
}

std::unique_ptr<Project>& PDCState::get_project()
{
    return project;
}