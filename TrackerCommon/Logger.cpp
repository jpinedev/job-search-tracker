#include "Logger.h"

void Logger::LogMessage(const std::string& message)
{
#ifdef DEBUG
    mOut << message << std::endl;
#endif
}
void Logger::LogMessage(const std::string& messageOrigin, const std::string& message)
{
#ifdef DEBUG
    PrependMessageOrigin(messageOrigin);
    LogMessage(message);
#endif
}
void Logger::LogError(const std::string& message)
{
#ifdef DEBUG
    mOut << "ERROR: ";
    LogMessage(message);
#endif
}
void Logger::LogError(const std::string& errorOrigin, const std::string& message)
{
#ifdef DEBUG
    PrependMessageOrigin(errorOrigin);
    LogError(message);
#endif
}

void Logger::PrependMessageOrigin(const std::string& messageOrigin)
{
#ifdef DEBUG
    mOut << '[' << messageOrigin << "] ";
#endif
}

