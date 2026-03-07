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
     * verifications must be done in the graph level
     */
    Edge(Id from_n, Id from_o, Id to_n, Id to_i)
    {
        from_node = from_n;
        from_output = from_o;
        to_node = to_n;
        to_input = to_i;
    }

    Edge(const nlohmann::json& j)
    {
        //TODO
    }


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

    static std::string class_name()
    {
        return "Edge";
    }

    nlohmann::json to_json(void)
    {
        return {{"id", id}, {"from_node", from_node}, {"from_output", from_output}, {"to_node", to_node}, {"to_input", to_input}};
    }
};

#endif