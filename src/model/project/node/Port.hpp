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
struct ValueConstraints
{
public:
    ValueConstraints() = default;
    optional<T> min;
    optional<T> max;
    optional<T> step;

    optional<vector<T>> allowed_values;

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

template<typename T>
class Port : public Identifiable<Port<T>>
{
public:
using Identifiable<Port<T>>::id;

    Port() = default;

    T data;
    enum PortDirection dir;
    enum ConnectionMode mode;

    optional<ValueConstraints<T>> constraints;

    vector<Id> incoming_edge;

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

    string get_str()
    {
        return get_str(0);
    }

    string get_str(unsigned int tab)
    {
        string s = "";
        string s_tab = Tab::tab(tab);

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

        s += ", type=" + data.get_str() + ";";

        return s;
    }

    static string class_name()
    {
        return "Port<" + T::class_name() + ">";
    }
};


#endif
