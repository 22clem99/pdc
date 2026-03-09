#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>
#include <memory>
#include <filesystem>
#include <string>
#include <QObject>

#include "graph/GraphEditor.hpp"
#include <utils/JSONPrintable.hpp>
#include <utils/Types.hpp>

enum class ProjectState
{
    Saved,
    Dirty
};

enum class SaveProjectStatus
{
    Saved,
    FailedToCreateTemp,
    FailedToAddFile,
    FailedToRenameTemp,
    FailedToGetImgExtension,
    FailedToEncodeImg,
    EncodeErrorUnknow
};

enum class OpenProjectStatus
{
    Opened,
    ProjectDoesNotExist,
    CantOpenArchive,
    ManifestNotFound,
    ManifestParsingError
};

class Project : public QObject
{
    Q_OBJECT

private:
    std::string name;
    std::filesystem::path file;

    ProjectState state;

    GraphEditor node_graph;

    Image input_image;

public:
    Project(const std::string& project_name, const std::filesystem::path file_path, const std::filesystem::path img_path);

    // Constructor when laoding a project from a file
    Project(const std::filesystem::path& path);

    int add_node(const std::string& node_type, unsigned int position);
    int remove_node(const std::string& node_type);

    bool is_dirty(void);

    std::string get_str();
    std::string get_str(const unsigned int tab);
    std::string get_name();

    // Method to construc recursivly the json project file
    nlohmann::json to_json(void);

    static std::string get_extension();

    SaveProjectStatus save(void);

    static OpenProjectStatus is_project_file_valid(const std::filesystem::path& path);

    static bool is_json_valid(const nlohmann::json& j);

    Image get_input_image(void);

signals:
    void image_changed(const Image& img);
};

#endif