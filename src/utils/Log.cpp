#include <iostream>

#include "Log.hpp"

void Log::debug(string msg) {
    instance().debug_impl(msg);
}

void Log::info(string msg) {
    instance().info_impl(msg);
}

void Log::warning(string msg) {
    instance().warning_impl(msg);
}

void Log::error(string msg) {
    instance().error_impl(msg);
}

void Log::critical(string msg) {
    instance().critical_impl(msg);
}

void Log::set_level(LogLevel new_level) {
    instance().set_level_impl(new_level);
}

// Implementation methods
void Log::debug_impl(string msg) {
    if (level <= LogLevel::DEBUG) {
        cout << "DEBUG: " << msg << endl;
    }
}

void Log::info_impl(string msg) {
    if (level <= LogLevel::INFO) {
        cout << "INFO: " << msg << endl;
    }
}

void Log::warning_impl(string msg) {
    if (level <= LogLevel::WARNING) {
        cout << "WARNING: " << msg << endl;
    }
}

void Log::error_impl(string msg) {
    if (level <= LogLevel::ERROR) {
        cout << "ERROR: " << msg << endl;
    }
}

void Log::critical_impl(string msg) {
    if (level <= LogLevel::CRITICAL) {
        cout << "CRITICAL: " << msg << endl;
    }
}

void Log::set_level_impl(LogLevel new_level) {
    level = new_level;
}
