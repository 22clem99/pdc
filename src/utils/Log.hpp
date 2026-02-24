#ifndef LOG_H
#define LOG_H

#include "Singleton.hpp"

#include <string>

using namespace std;

enum LogLevel
{
    DEBUG    = 0,
    INFO     = 1,
    WARNING  = 2,
    ERROR    = 3,
    CRITICAL = 4
};

class Log : public Singleton<Log>
{
    friend class Singleton<Log>; // Permet au Singleton d'accéder au constructeur

private:
    LogLevel level = ERROR;
    Log() = default;

public:
    // Public interface to log messages
    static void debug(string msg);
    static void info(string msg);
    static void warning(string msg);
    static void error(string msg);
    static void critical(string msg);
    static void set_level(LogLevel level);

private:
    // Log methods implementation
    void debug_impl(string msg);
    void info_impl(string msg);
    void warning_impl(string msg);
    void error_impl(string msg);
    void critical_impl(string msg);
    void set_level_impl(LogLevel level);
};

#endif