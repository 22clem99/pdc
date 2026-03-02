#include "Int.hpp"
#include <utils/Tab.hpp>

Int::Int(void)
{
    data = 0;
}

void Int::copy(const Int& a)
{
    data = a.data;
}

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

std::string Int::class_name(void)
{
    return "Int";
}

std::string Int::get_str() const
{
    return get_str(0);
}

std::string Int::get_str(const unsigned int tab) const
{
    return Tab::tab(tab) + "Int, value=" + std::to_string(data);
}