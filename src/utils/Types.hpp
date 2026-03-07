#ifndef TYPES_H
#define TYPES_H

#include <type_traits>
#include <concepts>

#include "Int.hpp"
#include "Image.hpp"
#include "Id.hpp"

template<typename T>
struct is_constrainable : std::false_type {};

template<>
struct is_constrainable<Int> : std::true_type {};

template<>
struct is_constrainable<Image> : std::false_type {};

template<typename T>
concept Constrainable = is_constrainable<T>::value;

#endif