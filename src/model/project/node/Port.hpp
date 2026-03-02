#ifndef PORT_H
#define PORT_H

#include <utils/Identifiable.hpp>
#include <utils/Tab.hpp>

#include <list>
#include <map>
#include <string>
#include <optional>
#include <ostream>
#include <sstream>
#include <memory>


enum class PortDirection {
    Input,
    Output
};

enum ConnectionMode {
    None,
    Single,
    Multiple
};

template<typename T>
class ValueConstraints
{
public:
    ValueConstraints() = default;
    std::optional<T> min;
    std::optional<T> max;
    std::optional<T> step;

    std::optional<std::vector<T>> allowed_values;

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

class IPortBase
{
public:
    virtual ~IPortBase() = default;

    virtual const std::type_info& value_type() const = 0;
    virtual std::string get_str() const = 0;
    virtual std::string get_str(unsigned int tab) const = 0;

    virtual PortDirection get_direction() const = 0;
    virtual ConnectionMode get_connection_mode() const = 0;
    virtual std::vector<Id> get_connected_edges() const = 0;
    virtual void add_connected_edge(const Id& edge_id) = 0;

    static bool same_type(const IPortBase& a, const IPortBase& b)
    {
        return a.value_type() == b.value_type();
    }
};

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
};

#endif
