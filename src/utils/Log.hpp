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

class Log
{
private:
    LogLevel level = ERROR;

    static Log& instance()
    {
        static Log instance; // garanti thread-safe depuis C++11
        return instance;
    }

public:
    // Public interface to log messages
    static void debug(const string& msg);
    static void info(const string& msg);
    static void warning(const string& msg);
    static void error(const string& msg);
    static void critical(const string& msg);
    static void set_level(LogLevel new_level);

private:
    // Log methods implementation
    void debug_impl(const string& msg) const;
    void info_impl(const string& msg) const;
    void warning_impl(const string& msg) const;
    void error_impl(const string& msg) const;
    void critical_impl(const string& msg) const;
    void set_level_impl(LogLevel new_level);
};

#endif