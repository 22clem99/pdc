#ifndef TAB_H
#define TAB_H

#include <string>

class Tab
{
public:
    static string tab(const unsigned int n)
    {
        string s = "";

        for (unsigned int i = 0; i < n; i++){
            s += "\t";
        }

        return s;
    }
};

#endif