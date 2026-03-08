/**
 * @file ImageRGBSplitterNode.hpp
 * @brief Define the Image Channel Splitter Node
 *
 *              Image
 *                |
 *                v
 *  +---------------------------+
 *  |                           |
 *  |    ImageRGBSplitterNode   |
 *  |                           |
 *  +------+------+------+------+
 *         |      |      |
 *         v      |      v
 *       Image    v    Image
 *         R    Image    B
 *      Channel   G   Channel
 *             Channel
 */

#ifndef IMAGE_RGB_SPLITTER_NODE_H
#define IMAGE_RGB_SPLITTER_NODE_H

#include <string>

#include "Node.hpp"
#include "NodeRegister.hpp"
#include "Port.hpp"

/**
 * @brief Define ImageRGBSplitterNode, a specific Node
 *
 * This node is used to split channel RGB of an image
 */
class ImageRGBSplitterNode : public Node
{
public:
    static constexpr NodeKind kind = NodeKind::Regular;

    /**
     * @brief Construct a new Image Input Node object
     *
     * This constructor append all port need by the node
     */
    ImageRGBSplitterNode();

    ImageRGBSplitterNode(const nlohmann::json& j);

    static std::string class_name();

    std::string get_class_name() const override { return class_name(); }

    /**
     * @brief Get the kind object
     *
     * @return NodeKind
     */
    NodeKind get_kind(void);

   /**
     * @brief Get the string representation of the ImageRGBSplitterNode
     *
     * @return std::string ImageRGBSplitterNode representation
     */
    std::string get_str(void);

    /**
     * @brief Same as get_str(void) but with tab at each lines
     *
     * @param tab number of tab to insert
     * @return std::string ImageRGBSplitterNode representation
     */
    std::string get_str(const unsigned int tab);

    /**
     * @brief This function compute output depending of inputs
     *
     * @return int
     */
    int compute_output();

private:
    inline static NodeRegister<ImageRGBSplitterNode> reg;
};

#endif