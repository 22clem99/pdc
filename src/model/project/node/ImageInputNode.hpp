#ifndef IMAGE_INPUT_NODE_H
#define IMAGE_INPUT_NODE_H

#include "Node.hpp"
#include "NodeRegister.hpp"

#include "Port.hpp"
#include <string>

using namespace std;


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
    static string class_name();
    string get_class_name() const override { return class_name(); }
    NodeKind get_kind(void);
    string get_str(void);
    string get_str(const unsigned int tab);
    int compute_output();

private:
    inline static NodeRegister<ImageInputNode> reg;
};

#endif