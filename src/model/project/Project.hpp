#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>

#include "node/Node.hpp"

using namespace std;

class Project
{
private:
    string name;
    string file;

    map<string, Node> nodes;

public:
    Project(/* args */);
    int add_node(string node_type, unsigned int position);
    int remove_node(string node_type);
};

#endif