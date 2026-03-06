#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>
#include <memory>
#include <filesystem>
#include <string>

#include "graph/GraphEditor.hpp"

enum class ProjectState
{
    Saved,
    Dirty
};

class Project
{
private:
    std::string name;
    std::filesystem::path file;

    ProjectState state;

    GraphEditor node_graph;

public:
    Project(const std::string& project_name, const std::filesystem::path file_path, const std::filesystem::path img_path);
    int add_node(const std::string& node_type, unsigned int position);
    int remove_node(const std::string& node_type);

    bool is_dirty(void);

    std::string get_str();
    std::string get_str(const unsigned int tab);

    static std::string get_extension();

};

#endif