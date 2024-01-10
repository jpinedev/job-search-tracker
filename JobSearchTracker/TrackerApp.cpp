#include "TrackerApp.h"
#include "TrackerCommon/Logger.h"

TrackerApp::TrackerApp(std::istream& in, std::ostream& out) :
    mIn(in),
    mOut(out),
    mCompaniesParser(CSVParser<Company::Schema_t>::FromFile("companies.csv")),
    mDatabase(mCompaniesParser) {}

void TrackerApp::Run()
{
    Logger logger;
    logger.LogMessage("TrackerApp", "Running...");
}
