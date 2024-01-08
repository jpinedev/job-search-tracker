#include "CompaniesDatabase.h"

Company& CompaniesDatabase::AddCompany(std::string name, std::string careersPageUrl)
{
    // TODO: implement
    return companies.front();
}

Company* CompaniesDatabase::GetCompany()
{
    // TODO: implement
    return nullptr;
}
const std::vector<Company>& CompaniesDatabase::GetCompanies()
{
    return companies;
}
