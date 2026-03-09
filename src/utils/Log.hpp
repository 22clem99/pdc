#ifndef LOG_H
#define LOG_H

#include <string>

enum LogLevel
{
    Debug    = 0,
    Info     = 1,
    Warning  = 2,
    Error    = 3,
    Critical = 4
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
    static void debug(const std::string& msg);
    static void info(const std::string& msg);
    static void warning(const std::string& msg);
    static void error(const std::string& msg);
    static void critical(const std::string& msg);
    static void set_level(LogLevel new_level);

private:
    // Log methods implementation
    void debug_impl(const std::string& msg) const;
    void info_impl(const std::string& msg) const;
    void warning_impl(const std::string& msg) const;
    void error_impl(const std::string& msg) const;
    void critical_impl(const std::string& msg) const;
    void set_level_impl(LogLevel new_level);
};

#endif