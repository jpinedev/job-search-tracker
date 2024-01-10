#include "InterestLevel.h"
#include <stdexcept>

std::istream& operator>>(std::istream& in, InterestLevel& level)
{
    int asNum;
    in >> asNum;
    
    if (asNum < (int)InterestLevel::NotRanked || asNum > (int)InterestLevel::Top)
        throw std::runtime_error("Unable to parse InterestLevel: index out of range");

    level = (InterestLevel)asNum;
    return in;
}

std::ostream& operator<<(std::ostream& out, InterestLevel level)
{
    return out << std::to_string(level);
}

namespace std
{
    string to_string(InterestLevel level)
    {
        switch (level)
        {
            case InterestLevel::NotRanked:
            case InterestLevel::Low:
            case InterestLevel::Medium:
            case InterestLevel::High:
            case InterestLevel::Top:
                return std::to_string((int)level);
            default:
                throw std::range_error("Not a valid InterestLevel");
        }
    }
}
