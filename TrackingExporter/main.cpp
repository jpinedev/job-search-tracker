#include <string>
#include <iostream>
#include "TrackerCommon/Logger.h"

int main(int argc, char** argv)
{
    Logger logger;
    logger.LogMessage("Hello");
    logger.LogError("World");
    return 0;
}
