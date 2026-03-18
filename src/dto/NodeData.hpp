#ifndef NODE_DATA_H
#define NODE_DATA_H

#include <vector>
#include <QPointF>

#include <utils/Id.hpp>

enum class PortTypes {
    Image,
    Int,
    Float,
    Error
};

struct PortData {
    Id port_id;
    PortTypes type;
};

struct NodeData {
    Id node_id;
    std::string pretty_print;
    QPointF position;
    std::vector<PortData> in_ports_data;
    std::vector<PortData> out_ports_data;
};

enum class NodeCreationTestStatus {
    TypeDoesNotExist,
    HeadAlreadyExist,
    TailAlreadyExist,
    OK
};

#endif