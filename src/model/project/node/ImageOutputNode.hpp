
#ifndef IMAGE_OUTPUT_NODE_H
#define IMAGE_OUTPUT_NODE_H

#include "Node.hpp"
#include "NodeRegister.hpp"

#include "Port.hpp"
#include <string>




/**
 * The Input Node is the image output node
 *            |
 *            V
 *  +---------+--------+
 *  |                  |
 *  | ImageOutput Node |
 *  |                  |
 *  +------------------+
 *
 */

class ImageOutputNode : public Node
{
public:
    static constexpr NodeKind kind = NodeKind::Tail;
    ImageOutputNode();
    static std::string class_name();
    std::string get_class_name() const override { return class_name(); }
    NodeKind get_kind(void);
    std::string get_str(void);
    std::string get_str(const unsigned int tab);
    int compute_output();

private:
    inline static NodeRegister<ImageOutputNode> reg;
};

#endif