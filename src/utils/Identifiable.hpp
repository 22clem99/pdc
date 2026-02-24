#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

#include <iostream>
#include <string>
#include <sstream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;

template<typename Derived>
class Identifiable
{
public:
    string id;
    Identifiable() {
        // Générateur UUID aléatoire
        static boost::uuids::random_generator generator;
        stringstream ss;

        boost::uuids::uuid uuid = generator();

        ss << uuid;

        id = Derived::ClassName() + "." + ss.str();
    }
};

#endif