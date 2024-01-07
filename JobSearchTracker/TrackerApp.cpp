#include "TrackerApp.h"
#include "TrackerCommon/hello.h"

TrackerApp::TrackerApp(std::istream& in, std::ostream& out) : mIn(in), mOut(out) {}

void TrackerApp::Run()
{
    mOut << "running..." << std::endl;
    PrintMSG();
}
