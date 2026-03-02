/**
 * @file PDCState.hpp
 * @brief This class represent the Model part of a MVC architecture used in this project
 */

#ifndef PDCSTATE_H
#define PDCSTATE_H

#include <memory>

#include "project/Project.hpp"

/**
 * @brief PDCState class is the Model representation of MVC in this project
 *
 */
class PDCState {
private:
    std::unique_ptr<Project> prj;
public:
    PDCState();
    bool createProject(const std::string& name);
    bool closeProject();
    bool saveProject();
    bool renameProject();
};

#endif