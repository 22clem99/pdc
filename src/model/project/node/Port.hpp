/**
 * @file Port.hpp
 * @brief This file describe generic Ports
 *
 * A ports is an output ou input of graph's node
 */

#ifndef PORT_H
#define PORT_H

#include <list>
#include <map>
#include <string>
#include <optional>
#include <ostream>
#include <sstream>
#include <memory>

#include <utils/Identifiable.hpp>
#include <utils/Tab.hpp>

/**
 * @brief describe the direction of the Port
 *
 */
enum class PortDirection {
    Input,
    Output
};

/**
 * @brief Describe the connection mode
 *
 * None -> no connection available (mainly used for data to set by GUI)
 * Single -> One connection only is allowed
 * Multiple -> Port can be bind multiple time
 */
enum class ConnectionMode {
    None,
    Single,
    Multiple
};

/**
 * @brief The class ValueConstraints describe a generic interface to provite value constraint for Port
 *
 * @tparam T type of the Port
 */
template<typename T>
class ValueConstraints
{
public:
    ValueConstraints() = default;
    std::optional<T> min;
    std::optional<T> max;
    std::optional<T> step;

    std::optional<std::vector<T>> allowed_values;

    /**
     * @brief Test the value depending constraint setup
     *
     * @param value value to be tested
     * @return true the value is valid
     * @return false the value is not valid
     */
    bool validate(const T& value)
    {
        if (allowed_values)
        {
            return find(
                allowed_values->begin(),
                allowed_values->end(),
                value
            ) != allowed_values->end();
        }

        if (min && T::lesser(value, min))
        {
            return false;
        }

        if (max && T::greater(value, max))
        {
            return false;
        }

        if (step && T::is_divisible(value, step))
        {
            return false;
        }
        return true;
    }

};

/**
 * @brief Abstract class used as list of reference in Node
 *
 */
class IPortBase
{
public:
    virtual ~IPortBase() = default;

    /**
     * @brief abstract method to get the type of the port
     *
     * @return const std::type_info&
     */
    virtual const std::type_info& value_type(void) const = 0;

    /**
     * @brief abstract method to get the string representation of a port
     *
     * @return std::string representation of the port
     */
    virtual std::string get_str(void) const = 0;

    /**
     * @brief same as get_str(void) but with tabulation append at each line
     *
     * @param tab number of tabulation to append
     * @return std::string representation of the port with tabulations
     */
    virtual std::string get_str(unsigned int tab) const = 0;

    /**
     * @brief Get the direction value
     *
     * @return PortDirection
     */
    virtual PortDirection get_direction() const = 0;

    /**
     * @brief Get the connection mode
     *
     * @return ConnectionMode
     */
    virtual ConnectionMode get_connection_mode() const = 0;

    /**
     * @brief Get the connected edges
     *
     * @return std::vector<Id>
     */
    virtual std::vector<Id> get_connected_edges() const = 0;

    /**
     * @brief add an edge to the list of edge connected
     *
     * @param edge_id
     */
    virtual void add_connected_edge(const Id& edge_id) = 0;

    /**
     * @brief remove an edge from the list of edges connected
     *
     * @param edge_id
     * @return true if the edge is remove
     * @return false if the edge failed to be removed
     */
    virtual bool remove_connected_edge(const Id& edge_id) = 0;

    /**
     * @brief Function to compare type of two Ports
     *
     * As Port is a template, we need to compare port to bind them, so we use
     * this function
     *
     * @param a port a
     * @param b port b
     * @return true if type of the object a and object b is the same
     * @return false if type of the object a and object b is different
     */
    static bool same_type(const IPortBase& a, const IPortBase& b)
    {
        return a.value_type() == b.value_type();
    }
};

/**
 * @brief Effective implementation of Port
 *
 * Each object allocate of kind Port<T> inherit the
 * Identifiable class to provide a unique identifier.
 *
 * @tparam T Type of the port
 */
template<typename T>
class Port : public Identifiable<Port<T>>, public IPortBase
{
public:
using Identifiable<Port<T>>::id;

    Port(PortDirection p_dir, ConnectionMode p_mode)
    {
        data = T();
        dir = p_dir;
        mode = p_mode;
        connected_edges = {};
    }

    const std::type_info& value_type() const {
        return typeid(T);
    }

    T data;
    enum PortDirection dir;
    enum ConnectionMode mode;

    std::optional<ValueConstraints<T>> constraints;

    std::vector<Id> connected_edges;

    bool set_value(const T& value)
    {
        if (constraints && !constraints.validate(value))
        {
            return false;
        }
        data.copy(value);
        return true;
    }

    T get_value()
    {
        return data;
    }

    std::string get_str() const override
    {
        return get_str(0);
    }

    std::string get_str(unsigned int tab) const override
    {
        std::string s = "";
        std::string s_tab = Tab::tab(tab);

        s += s_tab + "id:\"" + id + "\", ";
        switch (dir)
        {
            case PortDirection::Input :
                s += "[Input]";
                break;
            case PortDirection::Output :
                s += "[Output]";
                break;
            default:
                s += "[Error]";
                break;
        }

        switch (mode)
        {
        case ConnectionMode::None :
            s += "(None)";
            break;
        case ConnectionMode::Single :
            s += "(Single)";
            break;
        case ConnectionMode::Multiple :
            s += "(Multiple)";
            break;
        default:
            s += "(Error)";
            break;
        }

        s += ", type=" + data.get_str() + ", connected_edges {\n";

        for (auto edge_id : connected_edges)
        {
            s += s_tab + "\t\t" + edge_id + "\n";
        }

        s += s_tab + "\t};";

        return s;
    }

    static std::string class_name()
    {
        return "Port<" + T::class_name() + ">";
    }

    PortDirection get_direction() const override
    {
        return dir;
    }

    ConnectionMode get_connection_mode() const override
    {
        return mode;
    }

    std::vector<Id> get_connected_edges() const override
    {
        return connected_edges;
    }


    void add_connected_edge(const Id& edge_id) override
    {
        connected_edges.push_back(edge_id);
    }

    bool remove_connected_edge(const Id& edge_id) override
    {
        return (std::erase(connected_edges, edge_id) == 1);
    }
};

#endif
