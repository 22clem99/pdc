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
    input_image = Image(img_path);
}

Project::Project(const std::filesystem::path& path)
{
    namespace fs = std::filesystem;

    Log::debug("Load the project from: " + path.string());

    // Open the ZIP project
    ZipReader zip = ZipReader::open(path);
    // get manifest file content
    auto manifest = zip.read_text_file(std::filesystem::path(ArchiveManifestPath));
    // parse manifest as a JSON
    nlohmann::json manifest_as_json = nlohmann::json::parse(manifest);

    // extract data from json
    name = manifest_as_json["name"];
    node_graph = GraphEditor(manifest_as_json["graph"]);
    // use the file parsed
    file = path;

    // extract the image
    zip.find_file_with_unknown_extension(ArchiveImagePath);
    auto image_from_archive = zip.read_binary_file(std::filesystem::path(ArchiveImagePath + ImageExtension::extension_to_string(zip.get_extension_status())));
    input_image = Image(image_from_archive, zip.get_extension_status());
}

int Project::add_node(const std::string& node_type, const QPointF& position)
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

void Project::set_dirty(void)
{
    state = ProjectState::Dirty;
}

void Project::clear_dirty(void)
{
    state = ProjectState::Saved;
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

    if(zip.get_return_status() != ZipWriterReturnStatus::Ok)
    {
        Log::error("Unable to create the temporary project file at: " + tmp_file.string());
        return SaveProjectStatus::FailedToCreateTemp;
    }

    // first get the project json configuration
    nlohmann::json project_as_json = to_json();

    Log::debug("Will create a project with the json :\n" + project_as_json.dump(4));

    // Then write the json to the project manifest
    zip.add_string(ArchiveManifestPath, project_as_json.dump(4));

    if(zip.get_return_status() != ZipWriterReturnStatus::Ok)
    {
        Log::error("Unable to add the file manifest.json to the project file: " + tmp_file.string());
        return SaveProjectStatus::FailedToAddFile;
    }

    // write the project image
    auto image_bin = input_image.encode_img();

    switch (input_image.get_encode_status())
    {
    case ImgEncodeStatus::ImgEncodeErrorNoExtension:
        Log::error("Unable to get the image extension");
        return SaveProjectStatus::FailedToGetImgExtension;
    case ImgEncodeStatus::ImgEncodeError:
        Log::error("Unable to encode the image");
        return SaveProjectStatus::FailedToEncodeImg;
    case ImgEncodeStatus::ImgEncodeSuccessfully:
        break;
    default:
        Log::error("Encode error unknow");
        return SaveProjectStatus::EncodeErrorUnknow;
    }

    zip.add_file(ArchiveImagePath + input_image.get_extension().value(), image_bin);

    if (zip.get_return_status() != ZipWriterReturnStatus::Ok)
    {
        Log::error("Unable to add Image to the archive");
        return SaveProjectStatus::FailedToAddFile;
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
        return SaveProjectStatus::FailedToRenameTemp;
    }

    return SaveProjectStatus::Saved;
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

    if (zip.get_return_status() != ZipReaderReturnStatus::Ok)
    {
        return OpenProjectStatus::CantOpenArchive;
    }

    // Check that the image is embedded
    if (!zip.find_file_with_unknown_extension(ArchiveImagePath))
    {
        Log::debug("Image not found");
        return OpenProjectStatus::ImageNotFound;
    }
    Log::debug("Image found with extension " + ImageExtension::extension_to_string(zip.get_extension_status()));

    // Check that the manifest is embedded in the project file
    auto manifest = zip.read_text_file(std::filesystem::path(ArchiveManifestPath));

    if (zip.get_return_status() != ZipReaderReturnStatus::Ok)
    {
        Log::debug("Unable to read the file " + ArchiveManifestPath + " from project archive");
        return OpenProjectStatus::ManifestNotFound;
    }

    Log::debug("File " + ArchiveManifestPath + " read successfully with the content: " + manifest);

    // Finally test that the manifest is valid
    nlohmann::json manifest_as_json = nlohmann::json::parse(manifest);

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

    Log::debug("Json parsing: name, PDCVersion and graph fields are there, continue with the graph analyse");

    return Graph::is_json_valid(j["graph"]);
}

Image Project::get_input_image(void)
{
    return input_image;
}


GraphEditor* Project::get_graph_editor(void)
{
    return &node_graph;
}