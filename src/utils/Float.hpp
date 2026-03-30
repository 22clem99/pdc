#ifndef FLOAT_F
#define FLOAT_F

#include <string>

#include <dto/NodeData.hpp>

class Float {
public:
    float data;
    Float();
    void copy(const Float& a);
    static bool equal(const Float& a, const Float& b);
    static bool greater(const Float& a, const Float& b);
    static bool lesser(const Float& a, const Float& b);
    static bool equal_and_greater(const Float& a, const Float& b);
    static bool equal_and_lesser(const Float& a, const Float& b);
    // static bool is_divisible(const Float& a, const Float& div);
    static std::string class_name(void);
    std::string get_str(void) const;
    std::string get_str(const unsigned int tab) const;
    static PortTypes get_port_type(void);
};

#endif