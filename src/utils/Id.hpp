/**
 * @file Id.hpp
 * @brief Generic header to provide a Id type
 *
 * In our case it is a string, but this abstraction is done in order to be
 * modify if it is needed.
 */

#ifndef ID_H
#define ID_H

#include <string>

typedef std::string Id;

const Id nullid = "";

#endif