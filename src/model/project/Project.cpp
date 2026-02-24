#include "Project.hpp"
#include <utils/Log.hpp>

Project::Project()
{
    nodes = {};
    empty = true;
}

int Project::set_name_and_file(string project_name, string file_path)
{
    Log::info("Create a new project with (Name: \"" + project_name + "\"), (file: \"" + file_path + "\")");
    name = project_name;
    file = file_path;

    empty = false;
}

int Project::add_node(string node_type, unsigned int position)
{

}

int Project::remove_node(string node_type)
{

}

string Project::get_str(void)
{

}


bool Project::is_empty(void)
{
    return empty;
}