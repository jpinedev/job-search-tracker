#pragma once
#include "Company.h"
#include "JobListing.h"

class CSVParser;

class CompaniesDatabase
{
public:
    // CompaniesDatabase(CSVParser& parser);

    Company& AddCompany(std::string name, std::string careersPageUrl);

    Company* GetCompany();
    const std::vector<Company>& GetCompanies();

private:
    std::vector<Company> companies;

};

