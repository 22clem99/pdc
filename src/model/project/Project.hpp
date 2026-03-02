#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>
#include <memory>

#include "graph/GraphEditor.hpp"



class Project
{
private:
    std::string name;
    std::string file;

    GraphEditor node_graph;

public:
    Project(const std::string& project_name, const std::string& file_path);
    int add_node(const std::string& node_type, unsigned int position);
    int remove_node(const std::string& node_type);
    std::string get_str();
    std::string get_str(const unsigned int tab);
};

#endif