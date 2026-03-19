/**
 * @file GraphEditor.hpp
 * @brief The object is a high level manipulation graph manipulator
 *
 * The goal of this class is to simplify graph handling
 */

#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include <QPointF>
#include <QObject>

#include "Graph.hpp"
#include <utils/Types.hpp>
#include <utils/JSONPrintable.hpp>
#include <dto/NodeData.hpp>
#include "../node/NodeAllocator.hpp"

class GraphEditor : public QObject
{
    Q_OBJECT

private:
    Graph node_graph;

public:
    GraphEditor();

    // Constructor when laoding a project from a file
    GraphEditor(const nlohmann::json& j);

    ~GraphEditor();

    NodeData add_node(const std::string& node_type, const QPointF& pos);

    bool remove_node(const Id& node_id);

    NodeCreationTestStatus can_add_node(const std::string& node_type);

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

    void set_node_position(const Id& id, const QPointF& position);
    QPointF get_node_position(const Id& id);

    std::vector<NodeData> get_nodes_data(void);
    // const std::vector<Edge*>& Edges() const

    std::string get_node_type(const Id& id);

signals:
    void node_position_changed(const Id& id, const QPointF& pos);
    void node_has_been_delete(const Id& id);
    void node_has_been_added(const NodeData& data);
};

#endif