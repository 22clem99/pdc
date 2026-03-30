#ifndef PROJECT_DATA_H
#define PROJECT_DATA_H

#include <string>
#include <optional>

struct ProjectData {
    std::string name;
    std::optional<std::string> img_path;
    std::optional<std::string> description;
};

#endif