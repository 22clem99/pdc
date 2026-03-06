#include "Project.hpp"
#include <utils/Log.hpp>
#include <utils/Tab.hpp>

Project::Project(const std::string& project_name, const std::filesystem::path file_path, const std::filesystem::path img_path)
{
    Log::info("Create a new project with (Name: \"" + project_name + "\"), (file: \"" + file_path.string() + "\")");
    name = project_name;
    file = file_path;

    // Create the file
}

int Project::add_node(const std::string& node_type, unsigned int position)
{
    return (node_graph.add_node(node_type, position) != "" ? -1 : 0);
}

int Project::remove_node(const std::string& node_type)
{

    return (node_graph.remove_node(node_type) ? -1 : 0);
}

bool Project::is_dirty(void)
{
    if (state == ProjectState::Dirty)
        return true;

    return false;
}

std::string Project::get_str()
{
    return get_str(0);
}

std::string Project::get_str(const unsigned int tab)
{
    std::string s = "";
    std::string s_tab = Tab::tab(tab);

    s   += s_tab + "Project {\n"
        + s_tab + "\tname: \"" + name + "\",\n"
        + s_tab +  "\tfile: \"" + file.string() + "\",\n"
        + s_tab + node_graph.get_str(tab + 1) + "\n"
        + s_tab + "}";

    return s;
}

std::string Project::get_extension()
{
    return ".pdc";
}