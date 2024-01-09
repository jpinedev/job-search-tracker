#pragma once
#include <iostream>

#include "TrackerCommon/CSVParser.h"
#include "TrackerCommon/CompaniesDatabase.h"
#include "TrackerCommon/Company.h"

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

    CSVParser<Company::Schema_t> mCompaniesParser;
    CompaniesDatabase mDatabase;

};
