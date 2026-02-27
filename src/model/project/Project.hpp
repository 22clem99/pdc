#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>
#include <memory>

#include "graph/Graph.hpp"

using namespace std;

class Project
{
private:
    string name;
    string file;

    Graph node_graph;

public:
    Project(const string& project_name, const string& file_path);
    int add_node(const string& node_type, unsigned int position);
    int remove_node(const string& node_type);
    string get_str(void);
};

#endif