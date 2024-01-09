#pragma once
#include "Company.h"
#include "JobListing.h"

template<typename T>
class CSVParser;

class CompaniesDatabase
{
public:
    CompaniesDatabase(CSVParser<Company::Schema_t>& parser);

    Company& AddCompany(std::string name, std::string careersPageUrl);

    Company* GetCompany();
    const std::vector<Company>& GetCompanies();

private:
    std::vector<Company> companies;

};

