/**
 * @file ImageOutputNode.hpp
 * @brief Define the Output Image Node
 *
 *          Image
 *            |
 *            V
 *  +---------+--------+
 *  |                  |
 *  | ImageOutput Node |
 *  |                  |
 *  +------------------+
 */
#ifndef IMAGE_OUTPUT_NODE_H
#define IMAGE_OUTPUT_NODE_H

#include <string>

#include "Node.hpp"
#include "NodeRegister.hpp"
#include "Port.hpp"

/**
 * @brief Define ImageOutputNode, a specific Node
 *
 * This node is used as the graph exit
 */
class ImageOutputNode : public Node
{
public:
    static constexpr NodeKind kind = NodeKind::Tail;

    static const std::vector<PortDef> port_defs;

    /**
     * @brief Construct a new Image Output Node object
     *
     * This constructor append all port need by the node
     */
    ImageOutputNode();

    ImageOutputNode(const nlohmann::json& j);

    static std::string class_name();

    std::string get_class_name() const override { return class_name(); }

    /**
     * @brief Get the kind object
     *
     * @return NodeKind
     */
    NodeKind get_kind(void);

   /**
     * @brief Get the string representation of the ImageOutputNode
     *
     * @return std::string ImageOutputNode representation
     */
    std::string get_str(void);

    /**
     * @brief Same as get_str(void) but with tab at each lines
     *
     * @param tab number of tab to insert
     * @return std::string ImageOutputNode representation
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
    inline static NodeRegister<ImageOutputNode> reg;
};

#endif