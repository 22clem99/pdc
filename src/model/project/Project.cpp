#include "Project.hpp"
#include <utils/Log.hpp>
#include <utils/Tab.hpp>
#include "version.hpp"
#include "utils/Zip/ZipWriter.hpp"
#include "utils/Zip/ZipReader.hpp"
#include "utils/JSONWrapper.hpp"

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

std::string Project::get_name()
{
    return name;
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

SaveProjectStatus Project::save(void)
{
    std::filesystem::path tmp_file = file;
    tmp_file.replace_extension("pdc.tmp");

    ZipWriter zip = ZipWriter::create(tmp_file);

    if(zip.get_return_status() != ZipWriterReturnStatus::OK)
    {
        Log::error("Unable to create the temporary project file at: " + tmp_file.string());
        return SaveProjectStatus::FAILED_TO_CREATE_TEMP;
    }

    // first get the project json configuration
    nlohmann::json project_as_json = to_json();

    Log::debug("Will create a project with the json :\n" + project_as_json.dump(4));

    // Then write the json to the project manifest
    zip.add_string("manifest.json", project_as_json.dump(4));

    if(zip.get_return_status() != ZipWriterReturnStatus::OK)
    {
        Log::error("Unable to add the file manifest.json to the project file: " + tmp_file.string());
        return SaveProjectStatus::FAILED_TO_ADD_FILE;
    }

    // Write over the project file with the temporary file
    std::error_code ec;

    // Remove the old project
    std::filesystem::remove(file, ec);
    // and rename the temporary project
    Log::debug("Trying to rename: " + tmp_file.string() + "to: " + file.string());
    std::filesystem::rename(tmp_file, file);

    if (ec)
    {
        return SaveProjectStatus::FAILED_TO_RENAME_TEMP;
    }

    return SaveProjectStatus::SAVED;
}

OpenProjectStatus Project::is_project_file_valid(const std::filesystem::path& path)
{
    namespace fs = std::filesystem;

    // First check that the file exist
    if (!fs::exists(path))
    {
        return OpenProjectStatus::ProjectDoesNotExist;
    }

    // Check it can be open as ZIP file
    ZipReader zip = ZipReader::open(path);

    if (zip.get_return_status() != ZipReaderReturnStatus::OK)
    {
        return OpenProjectStatus::CantOpenArchive;
    }

    // Check that the manifest is embedded in the project file
    auto manifest = zip.read_test_file(std::filesystem::path("manifest.json"));

    if (zip.get_return_status() != ZipReaderReturnStatus::OK)
    {
        return OpenProjectStatus::ManifestNotFound;
    }

    // Finally test that the manifest is valid
    nlohmann::json manifest_as_json = nlohmann::json::parse(manifest);

    Log::info(manifest_as_json.dump(4));

    if(!is_json_valid(manifest_as_json))
    {
        return OpenProjectStatus::ManifestParsingError;
    }

    return OpenProjectStatus::Opened;
}

bool Project::is_json_valid(const nlohmann::json& j)
{
    // first check that it is a JSON object
    if (!j.is_object())
    {
        return false;
    }

    JSON_REQUIRED_FIELD(j, "name", is_string);
    JSON_REQUIRED_FIELD(j, "PDCVersion", is_string);
    JSON_REQUIRED_FIELD(j, "graph", is_object);

    return Graph::is_json_valid(j["graph"]);
}