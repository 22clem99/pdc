#ifndef PDCSTATE_H
#define PDCSTATE_H

#include <memory>

#include "project/Project.hpp"


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