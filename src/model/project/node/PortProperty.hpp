/**
 * @file PortProperty.hpp
 * @brief Header to define the port property object used by the factory
 */

#ifndef PORT_PROPERTY_H
#define PORT_PROPERTY_H

#include <functional>

// forward declaration
class IPortBase;

/**
 * @brief This define is just to rename more consisly the allocation method call
 *
 */
typedef std::function<std::unique_ptr<IPortBase>()> CreatorFuncPort;

/**
 * @brief PortProperty is a class to provide to the factory the allocator and data to manage allocation
 *
 */
class PortProperty
{
public:
    CreatorFuncPort factory;
};

#endif