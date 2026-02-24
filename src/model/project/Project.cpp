#include "Project.hpp"
#include <utils/Log.hpp>

Project::Project(string project_name, string file_path)
{
    Log::info("Create a new project with (Name: \"" + project_name + "\"), (file: \"" + file_path + "\")");
    name = project_name;
    file = file_path;
}

int Project::add_node(string node_type, unsigned int position)
{
    return 0;
}

int Project::remove_node(string node_type)
{

    return 0;
}

string Project::get_str(void)
{
    string s = "";

    s += "Project {\n\tname: \"" + name + "\", file: \"" + file + "\"\n}";

    return s;
}
