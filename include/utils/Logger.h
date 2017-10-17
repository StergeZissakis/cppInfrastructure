#ifndef _LOGGER__H__
#define _LOGGER__H__

#include <chrono>  
#include <ctime>   
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>

class Logger
{
  public:
    Logger(const char * cname, const char *fname)
      : className(cname), functionName(fname)
    {
      this->log("Entered");
    }

    ~Logger()
    {
      this->log("Exited");
    }

    void log(const char *msg)                 const  { log_line(msg);             }
    void log(const std::string &str)          const { log_line(str.c_str());    }
    void log(const std::stringstream &stream) const { this->log(stream.str());  }

    static bool enabled;
  private:
    const std::string className;
    const std::string functionName;


    std::string dateAndTime() const {
      auto now = std::chrono::high_resolution_clock::now();
      auto timet = std::chrono::system_clock::to_time_t(now);
      struct tm tm;
      ::localtime_r(&timet, &tm);
      char buff[512] = {0};
      std::stringstream stream;
      std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", &tm); // TODO: add milliseconds
      stream << buff << " ";
      return stream.str();
    }

    std::string threadId() const {
      std::stringstream stream;
      stream << "#" << std::this_thread::get_id() << " ";
      return  stream.str();
    }

    std::string fullFunctionName() const {
      std::stringstream stream;
      stream << className << "::" << functionName << "->";
      return  stream.str();
    }

    void log_line(const char *message) const
    {
      if( !enabled )
        return;
      std::stringstream stream;
      stream  << dateAndTime() 
        << threadId()   
        << fullFunctionName() 
        << message;
      // TODO: possibly use a mutex lock guard here
      std::clog << stream.str() << std::endl;
    }
};
 
#endif
