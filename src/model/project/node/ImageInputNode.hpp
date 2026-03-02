#ifndef IMAGE_INPUT_NODE_H
#define IMAGE_INPUT_NODE_H

#include "Node.hpp"
#include "NodeRegister.hpp"

#include "Port.hpp"
#include <string>




/**
 * The Input Node is the image injection node
 *
 *  +-----------------+
 *  |                 |
 *  | ImageInput Node |
 *  |                 |
 *  +--------+--------+
 *           |
 *           v
 *         Image
 *
 */

class ImageInputNode : public Node
{
public:
    static constexpr NodeKind kind = NodeKind::Head;
    ImageInputNode();
    static std::string class_name();
    std::string get_class_name() const override { return class_name(); }
    NodeKind get_kind(void);
    std::string get_str(void);
    std::string get_str(const unsigned int tab);
    int compute_output();

private:
    inline static NodeRegister<ImageInputNode> reg;
};

#endif