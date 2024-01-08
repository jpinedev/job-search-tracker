#pragma once
#include <string>
#include <functional>

#include "Application.h"
#include "InterestLevel.h"

typedef std::string JobListingId;

/// One-to-one representation of a job listing on a company's career website.
struct JobListing
{
    typedef std::function<bool(const JobListing&)> Predicate;

    JobListing(std::string id, std::string title, std::string url);

    std::string companyId;
    JobListingId id;
    std::string title;
    std::string url;
    InterestLevel interest{InterestLevel::NotRanked};
    Application application;

    void Applied();
    void NextInterview();
    void TookCodingTest();
    void ReachedFinalStage();
    void Rejected();

};
