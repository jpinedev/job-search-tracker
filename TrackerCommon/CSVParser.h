#pragma once
#include <iostream>
#include <istream>
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
    static CSVParser FromFile(const std::string& filePath);

    /// Get the next row in the CSV table.
    /// @returns empty if there are no more rows, or the row does not fit the schema
    std::optional<Schema_t> GetNextRow();

    /// @returns true if the first row in the table does not match the schema
    bool HasTitleRow() const { return hasTitleRow; }

    /// @throws if HasTitleRow is false
    const std::vector<std::string>& GetTitleRow() const;

private:
    typedef std::array<std::string, std::tuple_size<Schema_t>{}> ColumnTitles;

    /// Parse the first row in the table as a title row.
    /// @modifies `hasTitleRow` when the csv file has a valid title row
    /// @returns empty if the first row in the table matches the schema
    ColumnTitles ParseTitleRow();

    /// Parse a row according to the schema.
    /// @throws if there are no more rows, or the row does not fit the schema
    Schema_t ParseRow(std::vector<std::string>::const_iterator row) const;

    const std::vector<std::string> allRowsInFile;
    std::vector<std::string>::const_iterator currentRow;

    const ColumnTitles titles;
    bool hasTitleRow{false};

};

inline std::vector<std::string> GetAllLines(std::istream& in)
{
    std::vector<std::string> lines;

    std::string line;
    while (std::getline(in, line))
    {
        lines.push_back(line);
    }
    return lines;
}

template<class Schema_t>
CSVParser<Schema_t>::CSVParser(std::istream& csvIn) : allRowsInFile(GetAllLines(csvIn)), titles(ParseTitleRow())
{
    currentRow = allRowsInFile.begin();
}

template<class Schema_t>
CSVParser<Schema_t> CSVParser<Schema_t>::FromFile(const std::string& filePath)
{
    std::ifstream infile(filePath);
    return CSVParser<Schema_t>(infile);
}

template<class Schema_t>
std::optional<Schema_t> CSVParser<Schema_t>::GetNextRow()
{
    Logger logger;
    if (currentRow == allRowsInFile.end())
    {
        logger.LogMessage("CSVParser", "Reached end of file, no more rows to parse.");
        return {};
    }

    try
    {
        return ParseRow(currentRow++);
    }
    catch (std::runtime_error& e)
    {
        std::size_t lineNum = currentRow - allRowsInFile.begin() - 1;
        logger.LogError("CSVParser", "Unable to parse row '" + std::to_string(lineNum) + "':\n\t" + e.what());
        return {};
    }
}

template<class Schema_t>
const std::vector<std::string>& CSVParser<Schema_t>::GetTitleRow() const
{
    if (!hasTitleRow)
        throw std::runtime_error("CSV table does not have title row.");

    return titles;
}

template<class Schema_t>
CSVParser<Schema_t>::ColumnTitles CSVParser<Schema_t>::ParseTitleRow()
{
    return {};
}

template<typename TupleLike, std::size_t I>
void TryGetAndSet(std::istream& rowIn, TupleLike& tuple)
{
    std::ws(rowIn);

    auto& element = std::get<I>(tuple);
    std::string cell;
    if (rowIn.eof() || !std::getline(rowIn, cell, ','))
        throw std::runtime_error("Unable to read CSV cell '" + std::to_string(I) + "'");

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
            if (cellAsStream.bad())
            {
                throw std::runtime_error("Bad input");
            }

            std::ws(cellAsStream);
            if (!cellAsStream.eof())
            {
                throw std::runtime_error("Expected type '" + std::string(typeid(ElementType).name()) + "'");
            }
        }
        catch (std::runtime_error& e)
        {
            throw std::runtime_error("Could not parse cell '" + std::to_string(I) + "' in row.\n\t" + e.what());
        }
    }

    if constexpr (I + 1 == std::tuple_size<TupleLike>{})
    {
        if (!rowIn.eof())
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
Schema_t CSVParser<Schema_t>::ParseRow(std::vector<std::string>::const_iterator row) const
{
    if (row == allRowsInFile.end())
    {
        throw std::runtime_error("No more rows.");
    }

    if (row->empty())
    {
        std::size_t lineNum = row - allRowsInFile.begin();
        throw std::runtime_error("Unexpected empty line");
    }

    Schema_t values;

    std::stringstream rowIn(*row);
    ParseTuple<Schema_t>(rowIn, values);

    return values;
}
