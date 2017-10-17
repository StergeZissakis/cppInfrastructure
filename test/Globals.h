#ifndef __GLOBALS__HH__
#define __GLOBALS__HH__

#include <sstream>
#include <memory>

struct Globals
{
  static std::shared_ptr<std::stringstream> clogStream;
};

#endif
