#ifndef NODE_DATA_H
#define NODE_DATA_H

#include <QPointF>

#include <utils/Types.hpp>

struct NodeData {
    Id node_id;
    std::string pretty_print;
    QPointF position;
};


#endif