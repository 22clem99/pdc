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
#include <dto/NodeData.hpp>

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
    ManifestParsingError,
    ImageNotFound
};

/**
 * @brief static variable with the formated name of the image with the separator depending of the OS
 *
 */
inline const std::string ArchiveImagePath = std::string(".") + std::filesystem::path::preferred_separator + "image";

/**
 * @brief static variable with the formated name of the manifest with the separator depending of the OS
 *
 */
inline const std::string ArchiveManifestPath = std::string(".") + std::filesystem::path::preferred_separator + "manifest.json";

class Project : public QObject
{
    Q_OBJECT

private:
    std::string name;
    std::filesystem::path file;

    ProjectState state;

    std::unique_ptr<GraphEditor> node_graph;

    Image input_image;

public:

    /**
     * @brief Construct a new Project object used when a new project is build from a location and with a name
     *
     * @param project_name
     * @param file_path
     * @param img_path
     */
    Project(const std::string& project_name, const std::filesystem::path file_path, const std::filesystem::path img_path);

    /**
     * @brief Construct a new Project object used when a project is load from a .pdc file
     *
     * @param path path od the .pdc file
     */
    Project(const std::filesystem::path& path);

    ~Project();

    /** TODO
     * @brief Used to add a node to the project
     *
     * @param node_type keyword of the node to add
     * @param position
     * @return int
     */
    NodeData add_node(const std::string& node_type, const QPointF& position);

    /** TODO
     * @brief remove a node from the project, will also remove edges
     *
     * @param node_type
     * @return int
     */
    int remove_node(const std::string& node_type);

    NodeCreationTestStatus can_add_node(const std::string& node_type);

    /**
     * @brief get the dirtiness of the project
     *
     * @return true the project is dirty (i.e modified and not saved)
     * @return false the project is saved
     */
    bool is_dirty(void);

    /**
     * @brief set the project dirty as it has been modify
     *
     */
    void set_dirty(void);

    /**
     * @brief set the project saved as it has been save
     *
     */
    void clear_dirty(void);

    std::string get_str();
    std::string get_str(const unsigned int tab);
    std::string get_name();

    /**
     * @brief use to construct the manifest, it will generate recursively the project as a JSON file
     *
     * @return nlohmann::json project as a JSON
     */
    nlohmann::json to_json(void);

    /**
     * @brief Get the extension of pdc project
     *
     * @return std::string return ".pdc"
     */
    static std::string get_extension();

    SaveProjectStatus save(void);

    static OpenProjectStatus is_project_file_valid(const std::filesystem::path& path);

    static bool is_json_valid(const nlohmann::json& j);

    Image get_input_image(void);

    GraphEditor* get_graph_editor(void);

    void set_node_position(const Id& id, const QPointF& position);

signals:
    void image_changed(const Image& img);
    void node_position_changed(const Id& id, const QPointF& pos);
};

#endif