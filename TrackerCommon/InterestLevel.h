#pragma once
#include <iostream>

/// Interest level for a company, role, etc.
/// Strictly ordered: use <=> to compare (NotRanked is the lowest).
enum class InterestLevel
{
    NotRanked = 0,
    Low,
    Medium,
    High,
    Top,
};

std::istream& operator>>(std::istream& in, InterestLevel& level);
std::ostream& operator<<(std::ostream& out, InterestLevel level);

namespace std
{
    string to_string(InterestLevel level);
}
