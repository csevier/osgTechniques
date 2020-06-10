#include "logfilehandler.hpp"

LogFileHandler::LogFileHandler(const std::string &file)
{
    mLogFile.open(file);
}

void LogFileHandler::notify(osg::NotifySeverity severity, const char *msg)
{
    mLogFile << msg;
}

LogFileHandler::~LogFileHandler()
{
    mLogFile.close();
}
