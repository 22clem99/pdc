#include "Float.hpp"
#include <utils/Tab.hpp>

Float::Float()
{
    data = 0.0;
}

void Float::copy(const Float& a)
{
    data = a.data;
}

bool Float::equal(const Float& a, const Float& b)
{
    return a.data == b.data;
}

bool Float::greater(const Float& a, const Float& b)
{
    return a.data > b.data;
}

bool Float::lesser(const Float& a, const Float& b)
{
    return a.data < b.data;
}

bool Float::equal_and_greater(const Float& a, const Float& b)
{
    return a.data >= b.data;
}

bool Float::equal_and_lesser(const Float& a, const Float& b)
{
    return a.data <= b.data;
}

std::string Float::class_name(void)
{
    return "Float";
}

std::string Float::get_str(void) const
{
    return get_str(0);
}

std::string Float::get_str(const unsigned int tab) const
{
    return Tab::tab(tab) + "Float, value=" + std::to_string(data);
}

PortTypes Float::get_port_type(void)
{
    return PortTypes::Float;
}
