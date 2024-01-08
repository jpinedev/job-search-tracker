#pragma once
#include <cstdint>
#include <string>

/// Status info for a job application. Holds historical data for future insights.
struct Application
{
    enum class Status
    {
        NotApplied,
        Applied,
        Interviewing,
        Rejected
    };

    Status status{Status::NotApplied};
    std::string alternateResumeUsed;
    std::string coverLetter;
    // TODO: refactor as list of interview dates 
    std::uint8_t interviewCount{0};
    // TODO: refactor as list of coding test dates (if any job has more than one test) 
    bool hadCodingTest{false};
    bool reachedFinalStage{false};

};
