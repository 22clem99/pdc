#include "Int.hpp"

using namespace std;

bool Int::equal(Int a, Int b)
{
    return  a.data == b.data;
}

bool Int::greater(Int a, Int b)
{
    return a.data > b.data;
}

bool Int::lesser(Int a, Int b)
{
    return a.data < b.data;
}

bool Int::equal_and_greater(Int a, Int b)
{
    return a.data >= b.data;
}

bool Int::equal_and_lesser(Int a, Int b)
{
    return a.data <= b.data;
}

bool Int::is_divisible(Int a, Int div)
{
    return ((a.data % div.data) == 0);
}

string Int::class_name(void)
{
    return "Int";
}

string Int::get_str(void)
{
    return "Int (value=" + to_string(data) + ")";
}