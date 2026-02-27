#include "Int.hpp"

using namespace std;

bool Int::equal(const Int& a, const Int& b)
{
    return  a.data == b.data;
}

bool Int::greater(const Int& a, const Int& b)
{
    return a.data > b.data;
}

bool Int::lesser(const Int& a, const Int& b)
{
    return a.data < b.data;
}

bool Int::equal_and_greater(const Int& a, const Int& b)
{
    return a.data >= b.data;
}

bool Int::equal_and_lesser(const Int& a, const Int& b)
{
    return a.data <= b.data;
}

bool Int::is_divisible(const Int& a, const Int& div)
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