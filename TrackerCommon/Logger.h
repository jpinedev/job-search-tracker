#pragma once
#include <iostream>

class Logger
{
public:
    Logger(std::ostream& out = std::cout) : mOut(out) {}

    template<typename T>
    Logger& operator<<(const T& toLog);

    void LogMessage(const std::string& message);
    void LogMessage(const std::string& messageOrigin, const std::string& message);
    void LogError(const std::string& message);
    void LogError(const std::string& errorOrigin, const std::string& message);
private:
    std::ostream& mOut;

    /// Keep track of the system that logged the message/error
    void PrependMessageOrigin(const std::string& messageOrigin);

};

template<typename T>
Logger& Logger::operator<<(const T& toLog)
{
    mOut << toLog;
    return *this;
}

