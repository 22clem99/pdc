#ifndef IMAGE_H
#define IMAGE_H

#include <string>



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
    static std::string class_name(void);
    std::string get_str(void) const;
    std::string get_str(const unsigned int tab) const;
};

#endif