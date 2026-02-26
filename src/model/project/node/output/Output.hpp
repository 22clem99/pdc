#ifndef OUTPUT_H
#define OUTPUT_H

#include <utils/Identifiable.hpp>

template<typename T>
class Output : public Identifiable<Output<T>>
{
private:
    T data;
public:

    Output() {}

    Output(T value) {
        data = value;
    }

    T get_value() {
        return data;
    }

    int set_value(T value) {
        data = value;
    }

    static string class_name() {
        return "Output<" + T::class_name() + ">";
    }
};

#endif