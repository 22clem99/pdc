#ifndef NODE_H
#define NODE_H

#include <string>
#include <map>
#include <variant>

#include <utils/Types.hpp>

#include "Port.hpp"

#include <utils/Identifiable.hpp>
#include <memory>

using namespace std;

enum class NodeKind {
    Head,
    Tail,
    Regular
};

class Node : public Identifiable<Node>
{
public:
    map<Id, PortVariant> ports;
    NodeKind kind;
    virtual ~Node() = default;
    static string class_name();
    virtual string get_class_name() const = 0;
    // virtual NodeKind kind() const = 0;
    int add_port(PortVariant& p);
    string get_str(void);
    string get_str(const unsigned int tab);
    virtual int compute_output() = 0;
};

#endif
