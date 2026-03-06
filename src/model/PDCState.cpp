/**
 * @file PDCState.cpp
 * @brief Implementation of the PDCState class
 */

#include <fstream>
#include <filesystem>
#include <memory>

#include "PDCState.hpp"
#include "project/Project.hpp"

PDCState::PDCState()
{
    state = PDCProjectState::NoProject;
}

bool PDCState::create_project(const std::string& prj_name, const std::string& prj_path, const std::string& img_path)
{
    namespace fs = std::filesystem;

    if(can_create_project(prj_path, img_path))
        return false;

    fs::path folder = fs::path(prj_path);
    fs::path img_path_to_copy = fs::path(img_path);

    // First alocate the project
    auto new_project = std::make_unique<Project>(prj_name, prj_path, img_path);

    if(new_project == nullptr)
        return false;

    fs::create_directories(folder / "assets");
    std::ofstream file(folder / "project.pdc");

    file << "{\n";
    file << "  \"name\": \"" << prj_name << "\",\n";
    file << "  \"version\": 1\n";
    file << "}\n";

    return true;
}

bool PDCState::close_project()
{
    return false;
}

bool PDCState::save_project()
{
    return false;
}

bool PDCState::rename_project(const std::string& prj_name)
{
    return false;
}

bool PDCState::can_create_project(const std::string& prj_path, const std::string& img_path)
{
    namespace fs = std::filesystem;

    // First test the project path
    std::filesystem::path path_to_test = std::filesystem::path(prj_path);

    if (fs::exists(path_to_test))
        return false;

    // Then test the image path
    std::filesystem::path img_to_test = std::filesystem::path(img_path);

    if (fs::exists(img_to_test))
        return false;

    return true;
}

bool PDCState::has_project()
{
    return false;
}
