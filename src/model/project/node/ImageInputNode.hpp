/**
 * @file ImageInputNode.hpp
 * @brief Define the Input Image Node
 *  +-----------------+
 *  |                 |
 *  | ImageInput Node |
 *  |                 |
 *  +--------+--------+
 *           |
 *           v
 *         Image
 */

#ifndef IMAGE_INPUT_NODE_H
#define IMAGE_INPUT_NODE_H

#include <string>

#include "Node.hpp"
#include "NodeRegister.hpp"
#include "Port.hpp"
#include <utils/JSONPrintable.hpp>

/**
 * @brief Define ImageInputNode, a specific Node
 *
 * This node is used as the graph entry
 */
class ImageInputNode : public Node
{
public:
    static constexpr NodeKind kind = NodeKind::Head;

    static const std::vector<PortDef> port_defs;

    /**
     * @brief Construct a new Image Input Node object
     *
     * This constructor append all port need by the node
     */
    ImageInputNode();

    ImageInputNode(const nlohmann::json& j);

    static std::string class_name();

    std::string get_class_name() const override { return class_name(); }

    /**
     * @brief Get the kind object
     *
     * @return NodeKind
     */
    NodeKind get_kind(void);

   /**
     * @brief Get the string representation of the ImageInputNode
     *
     * @return std::string ImageInputNode representation
     */
    std::string get_str(void);

    /**
     * @brief Same as get_str(void) but with tab at each lines
     *
     * @param tab number of tab to insert
     * @return std::string ImageInputNode representation
     */
    std::string get_str(const unsigned int tab);

    /**
     * @brief This function compute output depending of inputs
     *
     * @return int
     */
    int compute_output();

    static std::string get_pretty_print(void);

    static std::string get_description(void);

    static bool is_json_valid(const nlohmann::json& j);

private:
    inline static NodeRegister<ImageInputNode> reg;
};

#endif