#include "Project.hpp"
#include <utils/Log.hpp>
#include <utils/Tab.hpp>

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

string Project::get_str()
{
    return get_str(0);
}

string Project::get_str(const unsigned int tab)
{
    string s = "";
    string s_tab = Tab::tab(tab);

    s   += s_tab + "Project {\n"
        + s_tab + "\tname: \"" + name + "\",\n"
        + s_tab +  "\tfile: \"" + file + "\",\n"
        + s_tab + node_graph.get_str(tab + 1) + "\n"
        + s_tab + "}";

    return s;
}
