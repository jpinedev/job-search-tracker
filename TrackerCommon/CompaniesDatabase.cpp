#include "CompaniesDatabase.h"

#include "CSVParser.h"
#include "Logger.h"

CompaniesDatabase::CompaniesDatabase(CSVParser<Company::Schema_t>& parser)
{
    Logger logger;
    for (auto companyFieldsOpt = parser.GetNextRow(); companyFieldsOpt.has_value(); companyFieldsOpt = parser.GetNextRow())
    {
        auto& companyFields = companyFieldsOpt.value();
        logger.LogMessage("CompaniesDatabase", "Name: " + std::get<0>(companyFields) + "; URL: " + std::get<1>(companyFields) + "; InterestLevel: " + std::to_string(std::get<2>(companyFields)));
    }
}

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
