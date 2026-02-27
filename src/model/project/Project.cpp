#include "Project.hpp"
#include <utils/Log.hpp>

Project::Project(const string& project_name, const string& file_path)
{
    Log::info("Create a new project with (Name: \"" + project_name + "\"), (file: \"" + file_path + "\")");
    name = project_name;
    file = file_path;
}

int Project::add_node(const string& node_type, unsigned int position)
{
    return (node_graph.add_node(node_type, position) != "" ? -1 : 0);
}

int Project::remove_node(const string& node_type)
{

    return (node_graph.remove_node(node_type) ? -1 : 0);
}

string Project::get_str(void)
{
    string s = "";

    s += "Project {\n\tname: \"" + name + "\", file: \"" + file + "\"\n}";

    return s;
}
