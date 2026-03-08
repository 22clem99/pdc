/**
 * @file PortAllocator.hpp
 * @brief This class Port Allocator use to allocate dynamically ports
 */

#ifndef PORT_ALLOCATOR_H
#define PORT_ALLOCATOR_H

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include <optional>

#include "PortProperty.hpp"

/**
 * @brief PortAllocator is a registerd factory implementation class
 *
 * Each derived class from Port need to sign in to this
 * factory and then it will be possible to dynamically
 * allocate port object.
 */
class PortAllocator
{
public:
    /**
     * @brief Method to register a port to the factory
     *
     * @param name keyword of the object associate
     * @param property object associate with the keyword,
     * this object embed: the factory method associate
     * with the keyword and some information used by the
     * graph to avoid to allocate port uselessly.
     */
    static void register_port(const std::string& name, PortProperty property);

    /**
     * @brief Method to allocate an object of kind Port registerd in the factory
     *
     * @param port_type keyword of the port to allocate
     * @return std::unique_ptr<Port> pointer on the new object allocate
     */
    static std::unique_ptr<IPortBase> alloc_port(const std::string& port_type);

    /**
     * @brief Get the property object depending of the port keyword
     *
     * @param port_type port keyword
     * @return std::optional<PortProperty> properties
     */
    static std::optional<PortProperty> get_property(const std::string& port_type);

private:
    /**
     * @brief private function to get map corresponding to the factory registred items
     * this map is protected by a C++ singleton pattern
     *
     * @return std::unordered_map<std::string, PortProperty>&
     */
    static std::unordered_map<std::string, PortProperty>& registry();
};

#endif