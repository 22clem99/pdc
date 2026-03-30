/**
 * @file Edge.hpp
 * @brief Representation of a graph edge
 *
 * Provide an object Edge used in graph to link node
 */

#ifndef EDGE_H
#define EDGE_H

#include <string>

#include <utils/Types.hpp>
#include <utils/Identifiable.hpp>
#include <utils/Tab.hpp>
#include <utils/JSONPrintable.hpp>
#include <utils/JSONWrapper.hpp>
#include "../graph/Snapshot.hpp"

/**
 * @brief Object Edge each edge created is unique
 * by using Identifiable template.
 */
class Edge : public Identifiable<Edge>
{
public:
    Id from_node;
    Id from_output;

    Id to_node;
    Id to_input;

    /**
     * @brief Construct a new Edge object
     *
     * @param from_n Node from the edge begin
     * @param from_o Output of the node to be link
     * @param to_n Node to the edge end
     * @param to_i Input of the node to be link
     *
     * The Edge object does not check anything,
     * verifications must be done in the graph level.
     */
    Edge(const Id& from_n, const Id& from_o, const Id& to_n, const Id& to_i) : Identifiable()
    {
        init(from_n, from_o, to_n, to_i);
    }

    /**
     * @brief Construct a new object with an existing ID, used for snapshot
     *
     * @param from_n Node from the edge begin
     * @param from_o Output of the node to be link
     * @param to_n Node to the edge end
     * @param to_i Input of the node to be link
     *
     * The Edge object does not check anything,
     * verifications must be done in the graph level.
     */
    Edge(const Id& from_n, const Id& from_o, const Id& to_n, const Id& to_i, const Id& existing_id) : Identifiable(existing_id)
    {
        init(from_n, from_o, to_n, to_i);
    }

private:
    /**
     * @brief private init method to setup an edge
     *
     * @param from_n
     * @param from_o
     * @param to_n
     * @param to_i
     */
    void init(Id from_n, Id from_o, Id to_n, Id to_i)
    {
        from_node = from_n;
        from_output = from_o;
        to_node = to_n;
        to_input = to_i;
    }

public:
    /**
     * @brief Construct a new Edge object based on a JSON file
     *
     * @param j content of the file used to create the edge
     */
    Edge(const nlohmann::json& j)
    {
        id          = j["id"].get<std::string>();
        from_node   = j["from_node"].get<std::string>();
        from_output = j["from_output"].get<std::string>();
        to_node     = j["to_node"].get<std::string>();
        to_input    = j["to_input"].get<std::string>();
    }

    /**
     * @brief Destroy the Edge object
     *
     */
    ~Edge() = default;

    /**
     * @brief Get the object string to be display
     *
     * @return std::string string reprentation of the edge
     */
    std::string get_str(void)
    {
        return get_str(0);
    }

    /**
     * @brief Same as get_str(void) but with tabulation
     *
     * @param tab number of tabulation to be insert in front of each line
     * @return std::string string reprentation of the edge
     */
    std::string get_str(const unsigned int tab) const
    {
        return Tab::tab(tab) + "\tEdge {id:\"" + id + "\", from " + from_node + "[" + from_output + "], to " + to_node +  "[" + to_input + "]}";
    }

    /**
     * @brief Return the class name of the object, used to generate IDs
     *
     * @return std::string
     */
    static std::string class_name()
    {
        return "Edge";
    }

    /**
     * @brief Method used to write a JSON file recursively, used to save the project
     *
     * @return nlohmann::json
     */
    nlohmann::json to_json(void)
    {
        return {{"id", id}, {"from_node", from_node}, {"from_output", from_output}, {"to_node", to_node}, {"to_input", to_input}};
    }

    /**
     * @brief Method to validate the edge JSON description of project file
     *
     * @param j content of the file to check
     * @return true the edge JSON description is valid
     * @return false the edge JSON description is not valid
     */
    static bool is_json_valid(const nlohmann::json& j)
    {
        if (!j.is_object())
        {
            return false;
        }

        JSON_REQUIRED_FIELD(j, "id", is_string);
        JSON_REQUIRED_FIELD(j, "from_node", is_string);
        JSON_REQUIRED_FIELD(j, "from_output", is_string);
        JSON_REQUIRED_FIELD(j, "to_node", is_string);
        JSON_REQUIRED_FIELD(j, "to_input", is_string);


        Log::debug("Json parsing: edge is valid");

        return true;
    }

    /**
     * @brief Create a snapshot of the edge
     *
     * @return EdgeSnapshot snapshot representation object
     */
    EdgeSnapshot get_snapshot(void)
    {
        return EdgeSnapshot(id,
                            from_node,
                            from_output,
                            to_node,
                            to_input);
    }
};

#endif