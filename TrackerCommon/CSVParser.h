#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <fstream>
#include <optional>
#include <sstream>
#include <vector>

#include "Logger.h"

/// CSVParser must be created with a schema so it knows how to interpret a CSV row.
///
/// A schema is a tuple where each template argument represents its corresponding column in the CSV table.
template<class Schema_t>
class CSVParser
{
public:
    CSVParser(std::istream& csvIn);
    /// @throws if file cannot be opened
    CSVParser(const std::string& filePath);

    /// Get the next row in the CSV table.
    /// @returns empty if there are no more rows, or the row does not fit the schema
    std::optional<Schema_t> GetNextRow();

    /// @returns true if the first row in the table does not match the schema
    bool HasTitleRow() const { return hasTitleRow; }

    /// @throws if HasTitleRow is false
    const std::vector<std::string>& GetTitleRow() const;

private:
    /// If the first row is a title row, the titles will be stored in `titles`.
    /// @returns false if the first row in the table matches the schema
    bool TryParseTitleRow();

    /// Stores the next row into `nextRow` if the row can be parsed.
    /// @returns false if there are no more rows, or the row does not fit the schema
    bool TryParseNextRow(); 

    std::ifstream infile;
    std::istream& csvIn;
    std::vector<std::string> titles;
    std::optional<Schema_t> nextRow;
    bool hasTitleRow{false};

};


template<class Schema_t>
CSVParser<Schema_t>::CSVParser(std::istream& csvIn) : csvIn(csvIn)
{
    hasTitleRow = TryParseTitleRow();
}

template<class Schema_t>
CSVParser<Schema_t>::CSVParser(const std::string& filePath) : infile(filePath), csvIn(infile)
{
    hasTitleRow = TryParseTitleRow();
}

template<class Schema_t>
std::optional<Schema_t> CSVParser<Schema_t>::GetNextRow()
{
    auto ret = nextRow;
    TryParseNextRow();
    return ret;
}

template<class Schema_t>
const std::vector<std::string>& CSVParser<Schema_t>::GetTitleRow() const
{
    if (!hasTitleRow)
        throw std::runtime_error("CSV table does not have title row.");

    return titles;
}

template<class Schema_t>
bool CSVParser<Schema_t>::TryParseTitleRow()
{
    TryParseNextRow();
    return false;
}

template<typename TupleLike, std::size_t I>
void TryGetAndSet(std::istream& csvIn, TupleLike& tuple)
{
    std::ws(csvIn);

    auto& element = std::get<I>(tuple);
    std::string cell;
    if (!std::getline(csvIn, cell, ','))
        throw std::runtime_error("Unable to parse CSV cell");

    using ElementType = std::tuple_element_t<I, TupleLike>;

    if constexpr (std::is_same_v<ElementType, std::string>)
    {
        element = cell;
    }
    else
    {
        std::stringstream cellAsStream(cell);
        try
        {
            cellAsStream >> element;
        }
        catch (std::runtime_error& e)
        {
            throw std::runtime_error("Could not parse element '" + std::to_string(I) + "' in row.\n\t" + e.what());
        }
    }
    
    // if constexpr (I < std::tuple_size<TupleLike>{})
    // {
    //     char comma;
    //     csvIn >> comma;
    //     if (comma != ',')
    //         throw std::runtime_error("Could not parse element '" + std::to_string(I) + "' in row.");
    // }

    if constexpr (I + 1 == std::tuple_size<TupleLike>{})
    {
        if (!csvIn.eof())
            throw std::runtime_error("Row has too many elements for the schema.");
    }
}

template<typename TupleLike, std::size_t I = 0>
void ParseTuple(std::istream& csvIn, TupleLike& tuple)
{
    if constexpr (I < std::tuple_size<TupleLike>{})
    {
        TryGetAndSet<TupleLike, I>(csvIn, tuple);
        ParseTuple<TupleLike, I + 1>(csvIn, tuple);
    }
}

template<class Schema_t>
bool CSVParser<Schema_t>::TryParseNextRow()
{
    Logger logger;
    if (csvIn.bad() || csvIn.eof())
    {
        logger.LogMessage("CSVParser", "No more rows.");
        return false;
    }

    Schema_t values;

    std::string row;
    if (!std::getline(csvIn, row))
    {
        logger.LogError("CSVParser", "Could not read in row");
        return false;
    }

    std::stringstream rowIn(row);
    try
    {
        ParseTuple<Schema_t>(rowIn, values);
    }
    catch (std::runtime_error& e)
    {
        nextRow.reset();
        logger.LogError("CSVParser", e.what());
        return false;
    }

    nextRow = values;
    return true;
}

// template<class Schema_t>
// CSVParser<Schema_t>::
