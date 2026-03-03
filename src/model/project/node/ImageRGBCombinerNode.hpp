/**
 * @file ImageRGBCombinerNode.hpp
 * @brief Define the Image Channel combiner Node
 *
 *       Image         Image
 *         R    Image    B
 *      Channel   G   Channel
 *         |   Channel   |
 *         |      |      |
 *         |      |      |
 *         v      v      v
 *  +------+------+------+------+
 *  |                           |
 *  |    ImageRGBCombinerNode   |
 *  |                           |
 *  +---------------------------+
 *                |
 *                v
 *              Image
 */

#ifndef IMAGE_RGB_COMBINER_NODE_H
#define IMAGE_RGB_COMBINER_NODE_H

#include <string>

#include "Node.hpp"
#include "NodeRegister.hpp"
#include "Port.hpp"

/**
 * @brief Define ImageRGBCombinerNode, a specific Node
 *
 * This node is used to combine RGB channel to an image
 */
class ImageRGBCombinerNode : public Node
{
public:
    static constexpr NodeKind kind = NodeKind::Regular;

    /**
     * @brief Construct a new ImageRGBCombinerNode Object
     *
     * This constructor append all port need by the node
     */
    ImageRGBCombinerNode();

    static std::string class_name();

    std::string get_class_name() const override { return class_name(); }

    /**
     * @brief Get the kind object
     *
     * @return NodeKind
     */
    NodeKind get_kind(void);

   /**
     * @brief Get the string representation of the ImageRGBCombinerNode
     *
     * @return std::string ImageRGBCombinerNode representation
     */
    std::string get_str(void);

    /**
     * @brief Same as get_str(void) but with tab at each lines
     *
     * @param tab number of tab to insert
     * @return std::string ImageRGBCombinerNode representation
     */
    std::string get_str(const unsigned int tab);

    /**
     * @brief This function compute output depending of inputs
     *
     * @return int
     */
    int compute_output();

private:
    inline static NodeRegister<ImageRGBCombinerNode> reg;
};

#endif