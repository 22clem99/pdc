/**
 * @file PortRegister.hpp
 * @brief Provide a register class used by allocator
 */

#ifndef PORT_REGISTER_H
#define PORT_REGISTER_H

#include "PortAllocator.hpp"
#include "PortProperty.hpp"

/**
 * @brief Object to register port to the factory
 *
 * @tparam port object to instanciate a register object for the factory
 */
template<typename port>
class PortRegister
{
public:
    PortRegister()
    {
        PortAllocator::register_port(port::class_name(), {[]()
        {
            return std::make_unique<port>();
        }});
    }
};

#endif
