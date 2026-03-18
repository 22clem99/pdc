#ifndef LOG_H
#define LOG_H

#include <string>
#include <source_location>

enum LogLevel
{
    Debug2   = 7,
    Debug1   = 6,
    Debug0   = 5,
    Debug    = 4,
    Info     = 3,
    Warning  = 2,
    Error    = 1,
    Critical = 0
};

class Log
{
private:
    LogLevel level = LogLevel::Error;

    static Log& instance()
    {
        static Log instance;
        return instance;
    }

public:
    // Public interface to log messages
    static void debug(const std::string& msg, const std::source_location& loc = std::source_location::current());
    static void info(const std::string& msg);
    static void warning(const std::string& msg);
    static void error(const std::string& msg);
    static void critical(const std::string& msg);
    static void set_level(LogLevel new_level);

private:
    // Log methods implementation
    void debug_impl(const std::string& msg, const std::source_location& loc) const;
    void info_impl(const std::string& msg) const;
    void warning_impl(const std::string& msg) const;
    void error_impl(const std::string& msg) const;
    void critical_impl(const std::string& msg) const;
    void set_level_impl(LogLevel new_level);
};

#endif