#pragma once

/// Interest level for a company, role, etc.
/// Strictly ordered: use <=> to compare (NotRanked is the lowest).
enum class InterestLevel
{
    NotRanked,
    Low,
    Medium,
    High,
    Top,
};

