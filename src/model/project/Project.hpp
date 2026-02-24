#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>

#include <memory>

#include "node/Node.hpp"

using namespace std;

class Project
{
private:
    string name;
    string file;

    map<string, unique_ptr<Node>> nodes;

public:
    Project(string project_name, string file_path);
    int add_node(string node_type, unsigned int position);
    int remove_node(string node_type);
    string get_str(void);
};

#endif