#pragma once
#include <iostream>

class TrackerApp
{
public:
    TrackerApp(std::istream& in, std::ostream& out);

    void Run();

private:
    // void PromptAction();
    // void ParseAction();
    // void DoAction();

private:
    std::istream& mIn;
    std::ostream& mOut;

    // Tracker mTracker;

};
