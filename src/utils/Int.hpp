#ifndef INT_H
#define INT_H

#include <string>

using namespace std;

class Int {
public:
    int data;
    Int() = default;
    static bool equal(Int a, Int b);
    static bool greater(Int a, Int b);
    static bool lesser(Int a, Int b);
    static bool equal_and_greater(Int a, Int b);
    static bool equal_and_lesser(Int a, Int b);
    static bool is_divisible(Int a, Int div);
    static string class_name(void);
    string get_str(void);
};

#endif