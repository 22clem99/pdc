#ifndef PORT_CONSTRAINTS_H
#define PORT_CONSTRAINTS_H

#include <string>
#include <optional>

/**
 * @brief The class ValueConstraints describe a generic interface to provite value constraint for Port
 *
 * @tparam T type of the Port
 */
template<typename T>
class ValueConstraints
{
public:
    ValueConstraints() = default;
    std::optional<T> min;
    std::optional<T> max;
    std::optional<T> step;

    std::optional<std::vector<T>> allowed_values;

    /**
     * @brief Test the value depending constraint setup
     *
     * @param value value to be tested
     * @return true the value is valid
     * @return false the value is not valid
     */
    bool validate(const T& value)
    {
        if (allowed_values)
        {
            return find(
                allowed_values->begin(),
                allowed_values->end(),
                value
            ) != allowed_values->end();
        }

        if (min && T::lesser(value, min))
        {
            return false;
        }

        if (max && T::greater(value, max))
        {
            return false;
        }

        if (step && T::is_divisible(value, step))
        {
            return false;
        }
        return true;
    }

    bool is_json_valid(const nlohmann::json& j)
    {
        return false;
    }
};


#endif