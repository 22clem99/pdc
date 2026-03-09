#include <iostream>

#include "Log.hpp"

void Log::debug(const std::string& msg) {
    instance().debug_impl(msg);
}

void Log::info(const std::string& msg) {
    instance().info_impl(msg);
}

void Log::warning(const std::string& msg) {
    instance().warning_impl(msg);
}

void Log::error(const std::string& msg) {
    instance().error_impl(msg);
}

void Log::critical(const std::string& msg) {
    instance().critical_impl(msg);
}

void Log::set_level(LogLevel new_level) {
    instance().set_level_impl(new_level);
}

// Implementation methods
void Log::debug_impl(const std::string& msg) const {
    if (level <= LogLevel::Debug) {
        std::cout << "DEBUG: " << msg << std::endl;
    }
}

void Log::info_impl(const std::string& msg) const {
    if (level <= LogLevel::Info) {
        std::cout << "INFO: " << msg << std::endl;
    }
}

void Log::warning_impl(const std::string& msg) const {
    if (level <= LogLevel::Warning) {
        std::cout << "WARNING: " << msg << std::endl;
    }
}

void Log::error_impl(const std::string& msg) const {
    if (level <= LogLevel::Error) {
        std::cout << "ERROR: " << msg << std::endl;
    }
}

void Log::critical_impl(const std::string& msg) const {
    if (level <= LogLevel::Critical) {
        std::cout << "CRITICAL: " << msg << std::endl;
    }
}

void Log::set_level_impl(LogLevel new_level) {
    level = new_level;
}
