#ifndef NODE_H
#define NODE_H

#include <string>
#include <map>
#include <variant>

#include <utils/Types.hpp>

#include "input/Input.hpp"
#include "output/Output.hpp"

#include <utils/Identifiable.hpp>

using namespace std;

using InputVariant = variant<
    Input<Int>
>;

using OutputVariant = variant<
    Output<Int>
>;

class Node : public Identifiable<Node>
{
private:
    string id;
    map<string, InputVariant> inputs;
    map<string, OutputVariant> outputs;
public:
    virtual ~Node() = 0;
    static string class_name();
    int add_input(InputVariant &in);
    int add_output(OutputVariant &out);
    string get_str(void);
    virtual int compute_output() = 0;
};

#endif
