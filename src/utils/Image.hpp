#ifndef IMAGE_H
#define IMAGE_H

#include <string>

using namespace std;

class Image {
public:
    //int data;
    Image() = default;
    // static bool equal(Image a, Image b);
    // static bool greater(Image a, Image b);
    // static bool lesser(Image a, Image b);
    // static bool equal_and_greater(Image a, Image b);
    // static bool equal_and_lesser(Image a, Image b);
    // static bool is_divisible(Image a, Image div);
    static string class_name(void);
    string get_str(void);
};

#endif