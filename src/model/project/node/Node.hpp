#ifndef NODE_H
#define NODE_H

#include <string>
#include <map>
#include <variant>

#include <utils/Types.hpp>

#include "Port.hpp"

#include <utils/Identifiable.hpp>
#include <memory>



enum class NodeKind {
    Head,
    Tail,
    Regular
};

class Node : public Identifiable<Node>
{
public:
    std::map<Id, std::unique_ptr<IPortBase>> ports;
    NodeKind kind;
    virtual ~Node() = default;
    static std::string class_name();
    virtual std::string get_class_name() const = 0;
    // virtual NodeKind kind() const = 0;
    int add_port(IPortBase& p);
    std::string get_str(void);
    std::string get_str(const unsigned int tab);
    virtual int compute_output() = 0;
};

#endif
