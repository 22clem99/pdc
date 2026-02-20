#ifndef INPUT_H
#define INPUT_H

#include <utils/Identifiable.hpp>

#include <list>

enum InputControlType {
    NO_CONTROL,
    LIMIT_CONTROL,
    LIMIT_WITH_STEP_CONTROL,
    SET_VALUE_CONTROL
};


template<typename T>
class Input : public Identifiable<Input>
{
private:
    T data;
    T high_limit;
    T low_limit;
    T step;
    list<T> available_values;
    enum InputControlType control;

public:
    Input(T value) {
        control = NO_CONTROL;
        data = value;
    }

    Input(T value, T high_value, T low_value) : Input(data) {
        control = LIMIT_CONTROL;
        high_limit = high_value;
        low_limit = low_value;
    }

    Input(T value, T high_value, T low_value, T step_value) : Input(data, high_value, low_value)  {
        control = LIMIT_WITH_STEP_CONTROL;
        step = step_value
    }

    Input(T value, list<T> values) {
        control = SET_VALUE_CONTROL;
        available_values = values
    }

    T get_value() {
        return data;
    }

    int set_value(T value) {
        switch (control)
        {
        case NO_CONTROL:
            // Nothing to do as we do not need to
            break;
        case LIMIT_CONTROL:
            if (T.lesser(value, low_limit) || T.greater(value, high_limit)) {
                return false;
            }
            break;
        case LIMIT_WITH_STEP_CONTROL:
            if (T.lesser(value, low_limit) || T.greater(value, high_limit) || T.is_divisible(value, step)) {
                return false;
            }
            break;

        case SET_VALUE_CONTROL:
            /* code */
            break;

        default:
            break;
        }

        data = value;
    }
};

#endif