#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <unordered_map>
#include <string>
#include <optional>
#include <variant>

#include <utils/Id.hpp>
#include <utils/Types.hpp>

struct IntProperty
{
    Int value;
    Int min;
    Int max;
};

struct FloatProperty
{
    Float value;
    Float min;
    Float max;
};

struct ChoiceProperty
{
    int selected_index;
    std::vector<std::string> options;
};

struct BoolProperty
{
    bool value;
};

using PropertyValue = std::variant<
    IntProperty,
    // FloatProperty,
    ChoiceProperty,
    BoolProperty
>;

struct Property {
    std::string pretty_print;
    PropertyValue value;
};

struct Properties {
    std::unordered_map<Id, Property> props;
};

#endif