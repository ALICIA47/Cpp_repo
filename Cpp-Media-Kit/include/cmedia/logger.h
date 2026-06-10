#pragma once

#include <fstream>
#include <mutex>
#include <string>

namespace cmedia {

enum class LogLevel {
    Debug,
    Info,
    Warn,
    Error
};

class Logger {
public:
    static Logger& instance();

    void setLogFile(const std::string& filename);

    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

private:
    Logger() = default;
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(LogLevel level, const std::string& message);
    std::string levelToString(LogLevel level);
    std::string currentTime();

private:
    std::ofstream file_;
    std::mutex mutex_;
};

} // namespace cmedia