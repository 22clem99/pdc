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

using namespace std;

template<typename Derived>
class Identifiable
{
public:
    Id id;
    Identifiable() {
        // Générateur UUID aléatoire
        static boost::uuids::random_generator generator;
        stringstream ss;

        boost::uuids::uuid uuid = generator();

        ss << uuid;

        id = Derived::class_name() + "." + ss.str();

        Log::debug("ID generate id=\"" + id + "\"");
    }
};

#endif