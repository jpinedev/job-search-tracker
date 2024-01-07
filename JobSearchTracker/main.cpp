#include <string>
#include <iostream>
#include "TrackerApp.h"

int main(int argc, char** argv)
{
    TrackerApp tracker(std::cin, std::cout);

    tracker.Run();
    
    return 0;
}


