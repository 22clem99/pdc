#ifndef PDCSTATE_H
#define PDCSTATE_H

#include "project/Project.hpp"


class PDCState {
private:
    Project prj;
public:
    PDCState();
    bool createProject(string name);
    bool closeProject();
    bool saveProject();
    bool renameProject();
};

#endif