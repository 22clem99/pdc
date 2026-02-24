#ifndef OUTPUT_H
#define OUTPUT_H

#include <utils/Identifiable.hpp>

template<typename T>
class Output : public Identifiable<Output<T>>
{
private:
    T data;
public:
    Output(T data);
};

#endif