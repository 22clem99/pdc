#include <iostream>

#include "Log.hpp"

void Log::debug(string msg) {
    get_instance().debug_impl(msg);
}

void Log::info(string msg) {
    get_instance().info_impl(msg);
}

void Log::warning(string msg) {
    get_instance().warning_impl(msg);
}

void Log::error(string msg) {
    get_instance().error_impl(msg);
}

void Log::critical(string msg) {
    get_instance().critical_impl(msg);
}

void Log::set_level(LogLevel new_level) {
    get_instance().set_level_impl(new_level);
}

// Implementation methods
void Log::debug_impl(string msg) {
    if (level <= LogLevel::DEBUG) {
        cout << "DEBUG: " << msg;
    }
}

void Log::info_impl(string msg) {
    if (level <= LogLevel::INFO) {
        cout << "INFO: " << msg;
    }
}

void Log::warning_impl(string msg) {
    if (level <= LogLevel::WARNING) {
        cout << "WARNING: " << msg;
    }
}

void Log::error_impl(string msg) {
    if (level <= LogLevel::ERROR) {
        cout << "ERROR: " << msg;
    }
}

void Log::critical_impl(string msg) {
    if (level <= LogLevel::CRITICAL) {
        cout << "CRITICAL: " << msg;
    }
}

void Log::set_level_impl(LogLevel new_level) {
    level = new_level;
}
