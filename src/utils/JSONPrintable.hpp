#ifndef JSON_PRINTABLE_H
#define JSON_PRINTABLE_H

#include <concepts>

#include <json/json.hpp>

template <typename T>
concept JSONConstructible = requires(nlohmann::json j) {
    { T(j) } -> std::same_as<T>;
};

template <JSONConstructible T>
T load_from_json(const nlohmann::json& j)
{
    return T(j);
}

template <typename T>
concept has_print_json = requires(T a) {
    { a.print_json() } -> std::same_as<nlohmann::json>;
};

template <has_print_json T>
void dump_json(const T& obj)
{
    nlohmann::json j = obj.print_json();
    std::cout << j.dump(4) << std::endl; // indentation 4 espaces
}

#endif