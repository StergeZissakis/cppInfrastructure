#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <unistd.h>

#include <utils/Logger.h>

void usage()
{
  Logger log("Usage", "Function");
  log.log("Invalida command line parameter.");

  std::cout 
    << "" << std::endl
    << "" << std::endl
    << "" << std::endl;
    exit(-1);
}

// Enable the log
bool Logger::enabled = true;

int main(int argc, char **argv)
{
  // initialise the logger: redirect std::clog to a log file
  std::stringstream logFileName;
  logFileName << "MyProject." << ::getpid() << ".log";
  std::ofstream logFile(logFileName.str());
  std::streambuf *clogBuff = std::clog.rdbuf();
  std::clog.rdbuf(logFile.rdbuf());
  {
    Logger log("Main", "Function");

    std::map<std::string, std::string> params = { 
      {"", ""} };

    for(int i = 1; i < argc; ++i)
    {
      if( params.find(argv[i]) == params.end() || i + 1 > argc )
      {
        std::cout << "Unrecognised parameter [" << argv[i] << "]" << std::endl;
        usage();
      }

      std::stringstream str;
      str << argv[i + 1];
			std::string value = 0;
      str >> value;
      params[argv[i]] = value;
      ++i;
    }

  }
  std::clog.rdbuf(clogBuff);
  return 0;
}

