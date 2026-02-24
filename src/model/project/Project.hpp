#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>

#include "node/Node.hpp"

using namespace std;

class Project
{
private:
    bool empty;

    string name;
    string file;

    map<string, Node> nodes;

public:
    Project();
    int set_name_and_file(string project_name, string file_path);
    int add_node(string node_type, unsigned int position);
    int remove_node(string node_type);
    string get_str(void);
    bool is_empty(void);
};

#endif