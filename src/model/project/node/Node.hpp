/**
 * @file Node.hpp
 * @brief Define an sabstract Node class
 *
 * This kind of object are used in the graph each node
 * can embedded port to communicate to other nodes
 */

#ifndef NODE_H
#define NODE_H

#include <string>
#include <map>
#include <variant>
#include <memory>

#include <utils/Types.hpp>
#include "Port.hpp"
#include <utils/Identifiable.hpp>
#include <utils/JSONPrintable.hpp>

/**
 * @brief Kind of node
 *
 * Used for node that can only allocate once
 */
enum class NodeKind {
    Head,
    Tail,
    Regular
};

std::string node_kind_to_str(NodeKind kind);

/**
 * @brief Enum type to manage DFS graph visit
 *
 * Used for node that can only allocate once
 */
enum class VisitState
{
    NotVisited,
    Visiting,
    Visited
};

/**
 * @brief abstract class Node use by the graph class
 *
 * Each object allocate of kind Node inherit the
 * Identifiable class to provide a unique identifier
 */
class Node : public Identifiable<Node>
{
public:
    std::map<Id, std::unique_ptr<IPortBase>> ports;

    NodeKind kind;

    VisitState visite_state;

    Node() {}
    Node(const nlohmann::json& j) {}

    virtual ~Node() = default;

    static std::string class_name();

    virtual std::string get_class_name() const = 0;

    /**
     * @brief Get the string representation of the Node
     *
     * @return std::string Node representation
     */
    std::string get_str(void);

    /**
     * @brief Same as get_str(void) but with tab at each lines
     *
     * @param tab number of tab to insert
     * @return std::string Node representation
     */
    std::string get_str(const unsigned int tab);

    /**
     * @brief Abstract function to compute outputs, need to be implement in derived class
     *
     * @return int
     */
    virtual int compute_output() = 0;

    /**
     * @brief set the node visit state status (use for graph navigation)
     */
    void set_visit_status(VisitState state);

    /**
     * @brief get the node visit state status (use for graph navigation)
     */
    VisitState get_visit_status(void);

    /**
     * @brief clear the node visit state status (use for graph navigation)
     */
    void clear_visit_status(void);

    /**
     * @brief get a list of port by direction
     *
     * @param dir direction of ports
     */
    std::vector<Id> get_ports_from_direction(PortDirection dir);

    nlohmann::json to_json(void);

    static bool is_json_valid(const nlohmann::json& j);

    static std::string get_pretty_print(void);

    static std::string get_description(void);
};

#endif
