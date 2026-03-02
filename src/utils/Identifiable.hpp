/**
 * @file Identifiable.hpp
 * @brief This file provide a macanism to generate an ID for object derived
 */

#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

#include <iostream>
#include <string>
#include <sstream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Log.hpp"
#include "Id.hpp"

/**
 * @brief This class provide an abstraction mecanism to generate ID for all derived class from this one
 *
 * @tparam T class derived which need IDs at allocation
 */
template<typename T>
class Identifiable
{
public:
    Id id;
    Identifiable() {
        // Générateur UUID aléatoire
        static boost::uuids::random_generator generator;
        std::stringstream ss;

        boost::uuids::uuid uuid = generator();

        ss << uuid;

        id = T::class_name() + "." + ss.str();

        Log::debug("ID generate id=\"" + id + "\"");
    }
};

#endif