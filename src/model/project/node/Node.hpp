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

using PortVariant = variant<
    unique_ptr<Port<Int>>,
    unique_ptr<Port<Image>>
>;

class Node : public Identifiable<Node>
{
public:
    map<string, PortVariant> ports;
    virtual ~Node() = default;
    static string class_name();
    virtual string get_class_name() const = 0;
    int add_port(PortVariant& p);
    string get_str(void);
    virtual int compute_output() = 0;
};

#endif
