#include "gtest/gtest.h"
#include <utils/Logger.h>
#include "Globals.h"

#include <iostream>
#include <fstream>
#include <string>

bool Logger::enabled = true;
std::shared_ptr<std::stringstream> Globals::clogStream;

int main(int argc, char **argv) 
{
  std::stringstream *str = new std::stringstream();
  Globals::clogStream.reset(str);
  std::streambuf *clogBuff = std::clog.rdbuf();
  std::clog.rdbuf(str->rdbuf());

  ::testing::InitGoogleTest(&argc, argv);
  auto status =  RUN_ALL_TESTS();

  std::clog.rdbuf(clogBuff);
  return  status;
}
