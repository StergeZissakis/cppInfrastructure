#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <unistd.h>

#include <utils/Logger.h>
#include <Settings.h>
#include <MonteCarlo.h>

void usage()
{
  Logger log("Usage", "Function");
  log.log("Invalida command line parameter.");

  std::cout 
    << "gethurricaneloss [options] florida_landfall_rate florida_mean florida_stddev " << std::endl
    << "                           gulf_landfall_rate gulf_mean gulf_stddev"           << std::endl
    << "  options: -n, --num_monte_carlo_samples Number of samples to run"             << std::endl;
    exit(-1);
}

// Enable the log
bool Logger::enabled = true;

int main(int argc, char **argv)
{
  // initialise the logger: redirect std::clog to a log file
  std::stringstream logFileName;
  logFileName << "GetHurricaneLoss." << ::getpid() << ".log";
  std::ofstream logFile(logFileName.str());
  std::streambuf *clogBuff = std::clog.rdbuf();
  std::clog.rdbuf(logFile.rdbuf());
  {
    Logger log("Main", "Function");

    std::map<std::string, Settings::ValueType> params = { {"-n", 0}, 
      {"--num_monte_carlo_samples"  , 0},
      {"florida_landfall_rate", 0},
      {"florida_mean", 0},
      {"florida_stddev", 0},
      {"gulf_landfall_rate", 0},
      {"gulf_mean", 0},
      {"gulf_stddev", 0} };

    for(int i = 1; i < argc; ++i)
    {
      if( params.find(argv[i]) == params.end() || i + 1 > argc )
      {
        std::cout << "Unrecognised parameter [" << argv[i] << "]" << std::endl;
        usage();
      }

      std::stringstream str;
      str << argv[i + 1];
      Settings::ValueType value = 0;
      str >> value;
      params[argv[i]] = value;
      ++i;
    }

    if( params["-n"] == 0 && params["--num_monte_carlo_samples"] == 0 )
    {
      std::cout << "Numer of samples not specified or zero" << std::endl;
      usage();
    }

    for( const auto &p : params )
      if( p.second == 0 && !(p.first == "-n" || p.first == "--num_monte_carlo_samples") )
      {
        std::cout << "None of the parameters can have a zero value" << std::endl;
        usage();
      }

    log.log("Initialising settings...");
    Settings settings(params);
    log.log("Settings initialised");

    // the calculation
    log.log("Simalting Florida...");
    MonteCarloSimulator<double> floridaSim(settings.floridaRate, settings.floridaMean, settings.floridaStddev, settings.numMonteCarloSamples);
    double floridaLoss = floridaSim.simulateLoss();
    std::stringstream str;
    str << "Florida simulation ended with the value [" << floridaLoss << "]";
    log.log(str);

    log.log("Simalting Gulf...");
    MonteCarloSimulator<double> gulfSim(settings.gulfRate, settings.gulfMean, settings.gulfStddev, settings.numMonteCarloSamples);
    double gulfLoss = gulfSim.simulateLoss();
    str.str("");
    str << "Gulf  simulation ended with the value [" << gulfLoss << "]";
    log.log(str);

    double totalLoss = (floridaLoss + gulfLoss) / settings.numMonteCarloSamples;
    str.str("");
    str << "Total Loss is [" << totalLoss << "]";
    log.log(str);

    std::cout << "Total Loss: " << totalLoss << std::endl;


  }
  std::clog.rdbuf(clogBuff);
  return 0;
}

