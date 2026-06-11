#include "cmedia/logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace cmedia {

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
}

void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (file_.is_open()) {
        file_.close();
    }

    file_.open(filename, std::ios::out | std::ios::app);
}

void Logger::debug(const std::string& message) {
    log(LogLevel::Debug, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::Info, message);
}

void Logger::warn(const std::string& message) {
    log(LogLevel::Warn, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::Error, message);
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);

    std::string line = "[" + currentTime() + "] "
                     + "[" + levelToString(level) + "] "
                     + message;

    if (level == LogLevel::Error) {
        std::cerr << line << std::endl;
    } else {
        std::cout << line << std::endl;
    }

    if (file_.is_open()) {
        file_ << line << std::endl;
    }
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warn:
        return "WARN";
    case LogLevel::Error:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

std::string Logger::currentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};
    localtime_s(&localTime, &time);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

} // namespace cmedia