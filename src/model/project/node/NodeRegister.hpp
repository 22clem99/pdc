/**
 * @file NodeRegister.hpp
 * @brief Provide a register class used by allocator
 */

#ifndef NODE_REGISTER_H
#define NODE_REGISTER_H

#include "NodeAllocator.hpp"
#include "NodeProperty.hpp"

/**
 * @brief Object to register node to the factory
 *
 * @tparam node object to instanciate a register object for the factory
 */
template<typename node>
class NodeRegister
{
public:
    NodeRegister()
    {
        NodeAllocator::register_node(
            node::class_name(),
            NodeProperty{
                [](){return std::make_unique<node>();},
                [](const nlohmann::json& j){return std::make_unique<node>(j);},
                [](const nlohmann::json& j){return node::is_json_valid(j);},
                NodeDescriptor{
                    node::kind,
                    node::get_pretty_print(),
                    node::get_description()
                }
            }
        );
    }
};

#endif
