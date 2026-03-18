#include "PDCCMDLineParser.hpp"

PDCCMDLineParser::PDCCMDLineParser()
    : logLevelOption({"l", "log-level"}, "Set the log level (0=critical, 1=error, warning=2, info=3, debug={4,5,6,7})", "level", "3"),
          fileOption({"f", "file"}, "Input file name.", "name")
{
    setApplicationDescription("Point De Croix command line interface");

    addHelpOption();

    addOption(logLevelOption);
    addOption(fileOption);
}