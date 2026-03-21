#ifndef EDGE_DATA_H
#define EDGE_DATA_H

#include <vector>
#include <QPointF>

#include <utils/Id.hpp>

// enum class PortTypes {
//     Image,
//     Int,
//     Float,
//     Error
// };

// struct PortData {
//     Id port_id;
//     PortTypes type;
// };

struct EdgeData {
    Id edge_id;
    Id node_id_src;
    Id port_id_src;
    Id node_id_dst;
    Id port_id_dst;
};

enum class EdgeCreationTestStatus {
    DestNodeDoesNotExist,
    SrcNodeDoesNotExist,
    DestPortDoesNotExist,
    SrcPortDoesNotExist,
    PortAreNotTheSameType,
    SrcConnectionTypeIsWrong,
    DestNotAvailableOrNotSingle,
    OK
};

#endif