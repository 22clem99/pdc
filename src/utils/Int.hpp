#ifndef INT_H
#define INT_H

#include <string>



class Int {
public:
    int data;
    Int();
    void copy(const Int& a);
    static bool equal(const Int& a, const Int& b);
    static bool greater(const Int& a, const Int& b);
    static bool lesser(const Int& a, const Int& b);
    static bool equal_and_greater(const Int& a, const Int& b);
    static bool equal_and_lesser(const Int& a, const Int& b);
    static bool is_divisible(const Int& a, const Int& div);
    static std::string class_name(void);
    std::string get_str(void) const;
    std::string get_str(const unsigned int tab) const;
};

#endif