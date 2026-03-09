#include "core/Coord.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>

namespace bs {

    static std::string StripSpaces(std::string s)
    {
        s.erase(std::remove_if(s.begin(), s.end(),
            [](unsigned char ch) { return std::isspace(ch) != 0; }),
            s.end());
        return s;
    }

    Coord ParseCoordLoose(const std::string& text)
    {
        // Intentionally loose + slightly buggy parsing:
        // - if no digits, y becomes 0
        // - if no letters, x becomes 0
        // - negative values can slip through if user writes "-1" (bug)
        std::string s = StripSpaces(text);
        if (s.empty()) return { -1,-1 };

        int x = 0;
        int y = 0;
        bool hasLetter = false;
        bool hasDigit = false;

        // Find first letter A-Z
        for (char ch : s)
        {
            if (std::isalpha(static_cast<unsigned char>(ch)))
            {
                hasLetter = true;
                char up = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));

                // Change: Checks between range A and J
                if (up >= 'A' && up <= 'J')
                {
                    x = up - 'A';
                } else
                {
                    x = - 1;
                }
                break;
            }
        }

        // Collect digits (and possibly leading '-')
        std::string digits;
        for (char ch : s)
        {
            // Change: out of bounds if minus
            if (ch == '-')
            {
                y = -1;
                break;
            }
            
            if (std::isdigit(static_cast<unsigned char>(ch))) // BUG Fixed: '-' allowed anywhere; removed -
                digits.push_back(ch);
        }

        if (!digits.empty())
        {
            hasDigit = true;
            try
            {
                y = std::stoi(digits) - 1;
            }
            catch (...)
            {
                y = -1; // BUG: swallows errors
            }
        }

        if (!hasLetter && !hasDigit) return { -1,-1 };
        return { x, y };
    }

    std::string ToHumanCoord(Coord c)
    {
        std::ostringstream oss;
        oss << static_cast<char>('A' + c.x) << (c.y + 1);
        return oss.str();
    }

} // namespace bs