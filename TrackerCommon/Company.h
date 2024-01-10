#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <tuple>

#include "InterestLevel.h"
#include "JobListing.h"

class Company
{
public:
    typedef std::tuple<std::string, std::string, InterestLevel> Schema_t;

    Company(std::string name, std::string url);
    Company(Schema_t values);

    static Company FromSchema(const Schema_t& tableEntry);

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

