#include "gtest/gtest.h"
#include "utils/Logger.h"
#include "Globals.h"

#include <algorithm>

TEST(LoggerTest, CtorDtor)
{
  {
    Globals::clogStream->str("");
    
    Logger log("LoggerTest", "AutoObject");
    EXPECT_GT(Globals::clogStream->str().size(), 0);

    Globals::clogStream->str("");
  }
  EXPECT_GT(Globals::clogStream->str().size(), 0);
  Globals::clogStream->str("");
}

TEST(LoggerTest, logFunction)
{
  Globals::clogStream->str("");
  Logger log("LoggerTest", "LogFunction");
  Globals::clogStream->str("");
  
  std::string logMsg = "Test Message";
  log.log(logMsg);
  EXPECT_GT(Globals::clogStream->str().size(), 0);

  std::string clogCtx = Globals::clogStream->str();
  EXPECT_TRUE(std::search(clogCtx.begin(), clogCtx.end(), logMsg.begin(), logMsg.end()) != clogCtx.end());

}

TEST(LoggerTest, Disabled)
{
  Globals::clogStream->str("");
  Logger::enabled = false;
  {
    Logger log("LoggerTest", "Disabled");
    EXPECT_EQ(Globals::clogStream->str().size(), 0);
    log.log("sample test");
    EXPECT_EQ(Globals::clogStream->str().size(), 0);
  }
  Logger::enabled = true;
  EXPECT_EQ(Globals::clogStream->str().size(), 0);
}
