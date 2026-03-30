#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <map>
#include <QPointF>

#include <utils/Id.hpp>

struct PortSnapshot {
    Id port_id;
    std::string alias;

    // Will need to snapshot the value if needed
};

struct NodeSnapshot {
    Id node_id;
    std::string node_type;
    QPointF position;

    std::unordered_map<std::string, PortSnapshot> ports_snapshot;
};

struct EdgeSnapshot {
    Id edge_id;

    Id from_node;
    Id from_port;
    Id to_node;
    Id to_port;
};

#endif