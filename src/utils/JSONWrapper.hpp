#ifndef JSON_WRAPPER_H
#define JSON_WRAPPER_H

#define JSON_REQUIRED_FIELD(obj, name, typecheck) \
    Log::debug(std::string("Looking for: ") + name); \
    if (!obj.contains(name) || !obj[name].typecheck()) { \
        Log::debug(std::string(name) + " not found!"); \
        return false;} \
    Log::debug(std::string(name) + " found!");

#endif