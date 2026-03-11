#ifndef JSON_WRAPPER_H
#define JSON_WRAPPER_H

#define JSON_REQUIRED_FIELD(obj, name, typecheck) \
    if (!obj.contains(name) || !obj[name].typecheck()) { \
        return false;}

#endif