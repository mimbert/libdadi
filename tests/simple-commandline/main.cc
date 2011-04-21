#include <cstdlib>
#include <iostream>
// force debug traces in dadi::setProperty
#define NDEBUG

#include "config.hh"
#include "options.hh"


int main(int argc, char *argv[], char *envp[]) {
  dadi::Options opt;
  dadi::Config& config = dadi::Config::instance();

  opt.setName("simple-commandline");
  opt.setUsage("[-h] [options] -n <name> -j <number>");
  boost::function0<void> fHelp(boost::bind(dadi::help, boost::cref(opt)));
  boost::function1<void, std::string> fName(
    boost::bind(dadi::setPropertyString, "name", _1));
  boost::function1<void, int> fJobs(
    boost::bind(dadi::setProperty<int>, "jobs", _1));

  opt.addSwitch("help,h", "display help message", fHelp);
  opt.addOption("name,n", "name", fName);
  opt.addOption("jobs,j", "number of jobs", fJobs);

  opt.parseCommandLine(argc, argv);
  opt.notify();

  return EXIT_SUCCESS;
}
