#include "Project.hpp"
#include <utils/Log.hpp>
#include <utils/Tab.hpp>
#include "version.hpp"

Project::Project(const std::string& project_name, const std::filesystem::path file_path, const std::filesystem::path img_path)
{
    Log::info("Create a new project with (Name: \"" + project_name + "\"), (file: \"" + file_path.string() + "\")");
    name = project_name;
    file = file_path;

    // Create the file
}

Project::Project(const nlohmann::json& j)
{
    Log::debug("Load a project from a .pdc file");

    // if (j.contains("name") && j["name"].is_string())
    //     name = j["name"];
    // else
    //     throw std::runtime_error("Node: missing or invalid 'name'");

    // if (j.contains("id") && j["id"].is_number_integer())
    //     id = j["id"];
    // else
    //     throw std::runtime_error("Node: missing or invalid 'id'");

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


nlohmann::json Project::to_json(void)
{
    nlohmann::json json_file = {{"name", name},
                                {"PDCVersion", PROJECT_VERSION},
                                {"graph", node_graph.to_json()}};

    return json_file;
}

std::string Project::get_extension()
{
    return ".pdc";
}