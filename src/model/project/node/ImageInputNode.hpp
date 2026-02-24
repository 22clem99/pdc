#ifndef IMAGE_INPUT_NODE_H
#define IMAGE_INPUT_NODE_H

#include "Node.hpp"

#include "output/Output.hpp"


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

class ImageInputNode : Node
{
public:
    ImageInputNode();
    static string class_name();
    string get_str(void);
    int compute_output();
};

#endif