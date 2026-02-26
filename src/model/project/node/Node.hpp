#ifndef NODE_H
#define NODE_H

#include <string>
#include <map>
#include <variant>

#include <utils/Types.hpp>

#include "input/Input.hpp"
#include "output/Output.hpp"

#include <utils/Identifiable.hpp>
#include <memory>

using namespace std;

using InputVariant = variant<
    unique_ptr<Input<Int>>
>;

using OutputVariant = variant<
    unique_ptr<Output<Int>>,
    unique_ptr<Output<Image>>
>;

class Node : public Identifiable<Node>
{
public:
    map<string, InputVariant> inputs;
    map<string, OutputVariant> outputs;
    virtual ~Node() = default;
    static string class_name();
    virtual string get_class_name() const = 0;
    int add_input(InputVariant &in);
    int add_output(OutputVariant &out);
    string get_str(void);
    virtual int compute_output() = 0;
};

#endif
