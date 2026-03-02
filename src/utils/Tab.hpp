#ifndef TAB_H
#define TAB_H

#include <string>

class Tab
{
public:
    static std::string tab(const unsigned int n)
    {
        std::string s = "";

        for (unsigned int i = 0; i < n; i++){
            s += "\t";
        }

        return s;
    }
};

#endif