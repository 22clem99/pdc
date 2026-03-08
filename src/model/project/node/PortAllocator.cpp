/**
 * @file PortAllocator.cpp
 * @brief Implementing PortAllocator class
 *
 */

#include "PortAllocator.hpp"
#include "Port.hpp"
#include <utils/Log.hpp>

void PortAllocator::register_port(const std::string& name, PortProperty property)
{
    registry()[name] = property;
}

std::unique_ptr<IPortBase> PortAllocator::alloc_port(const std::string& port_type)
{
    Log::debug("Trying to alloc a port of type : \"" + port_type + "\"");
    auto it = registry().find(port_type);

    if (it == registry().end()) {
        Log::debug("Port type \"" + port_type + "\" doesn't exist, return a null pointer");
        return nullptr;
    }

    Log::debug("Port type \"" + port_type + "\" exist");

    return it->second.factory();
}

std::optional<PortProperty> PortAllocator::get_property(const std::string& port_type)
{
    Log::debug("Trying to get property with port type : \"" + port_type + "\"");
    auto it = registry().find(port_type);

    if (it == registry().end()) {
        Log::debug("Port type \"" + port_type + "\" doesn't exist, return a null pointer");
        return std::nullopt;
    }

    Log::debug("Port type \"" + port_type + "\" exist");

    return it->second;
}

std::unordered_map<std::string, PortProperty>& PortAllocator::registry()
{
    static std::unordered_map<std::string, PortProperty> instance;
    return instance;
}