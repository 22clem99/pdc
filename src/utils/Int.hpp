#ifndef INT_H
#define INT_H

#include <string>

using namespace std;

class Int {
public:
    int data;
    Int() = default;
    static bool equal(const Int& a, const Int& b);
    static bool greater(const Int& a, const Int& b);
    static bool lesser(const Int& a, const Int& b);
    static bool equal_and_greater(const Int& a, const Int& b);
    static bool equal_and_lesser(const Int& a, const Int& b);
    static bool is_divisible(const Int& a, const Int& div);
    static string class_name(void);
    string get_str(void);
};

#endif