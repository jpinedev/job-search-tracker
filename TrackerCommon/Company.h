#pragma once
#include <cstddef>
#include <string>
#include <vector>

#include "InterestLevel.h"
#include "JobListing.h"

class Company
{
public:
    Company(std::string name, std::string url);

    const std::string& GetName() const;
    const std::vector<JobListing>& GetListings() const;
    std::vector<const JobListing&> GetListings(JobListing::Predicate pred) const;
    std::size_t CountListings() const;
    std::size_t CountListings(JobListing::Predicate pred) const;

    JobListing& GetListing(JobListingId id);

    void UpdateName(std::string name);
    JobListing& CreateListing(JobListing listing);
    void RemoveListing(JobListingId listingId);

    std::string careersUrl;
    InterestLevel interest{InterestLevel::NotRanked};

private:
    std::string name;
    std::vector<JobListing> listings;

};

