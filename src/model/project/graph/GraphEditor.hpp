/**
 * @file GraphEditor.hpp
 * @brief The object is a high level manipulation graph manipulator
 *
 * The goal of this class is to simplify graph handling
 */

#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include "Graph.hpp"
#include <utils/Types.hpp>
#include <utils/JSONPrintable.hpp>

class GraphEditor
{
private:
    Graph node_graph;

public:
    GraphEditor() = default;

    // Constructor when laoding a project from a file
    GraphEditor(const nlohmann::json& j);

    Id add_node(const std::string& node_type, unsigned int position);

    bool remove_node(const Id& node_id);

    /**
     * @brief Get the string representation of the GraphEditor
     *
     * @return std::string GraphEditor representation
     */
    std::string get_str(void);

    /**
     * @brief Same as get_str(void) but with tab at each lines
     *
     * @param tab number of tab to insert
     * @return std::string GraphEditor representation
     */
    std::string get_str(const unsigned int tab);

    // Method to construc recursivly the json project file
    nlohmann::json to_json(void);
};

#endif