#ifndef LOGFILEHANDLER_HPP
#define LOGFILEHANDLER_HPP

#include <osgDB/ReadFile>
#include <fstream>


class LogFileHandler : public osg::NotifyHandler
{
    public:
        LogFileHandler() = delete;
        LogFileHandler(const std::string& file);
        virtual ~LogFileHandler();
        virtual void notify(osg::NotifySeverity severity, const char* msg) override;

    protected:
        std::ofstream mLogFile;
};

#endif // LOGFILEHANDLER_HPP
