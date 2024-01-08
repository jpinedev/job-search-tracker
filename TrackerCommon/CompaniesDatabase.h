#pragma once
#include "Company.h"
#include "JobListing.h"

class CSVParser;

class CompaniesDatabase
{
public:
    CompaniesDatabase();
    CompaniesDatabase(CSVParser& parser);

    Company& AddCompany(std::string name, std::string careersPageUrl);

    std::optional<Company&> GetCompany();
    const std::vector<Company>& GetCompanies();

private:
    std::vector<Company> companies;

};

