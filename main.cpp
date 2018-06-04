#include <algorithm>
#include <iostream>

#include "combinations.hpp"

int main()
{
    typedef std::vector<int> Set;
    typedef std::vector<Set> SetOfSets;
    typedef SetOfSets::const_iterator SetOfSetsCIt;
    const SetOfSets data = {{2, 4}, {1, 3, 8}, {7, 5}};
    {
        std::cout << "First to last-------" << std::endl;
        typedef combinations<SetOfSetsCIt> Combinations;
        Combinations cmbs = make_combinations(data);
        {
            std::cout << "Forward:" << std::endl;
            for(const auto& combination : cmbs)
            {
                for(const auto& elemIt : combination)
                    std::cout << *elemIt << " ";
                std::cout << std::endl;
            }
        }
        {
            std::cout << "Reverse:" << std::endl;
            for(Combinations::const_reverse_iterator combIt = cmbs.crbegin();
                combIt != cmbs.crend();
                ++combIt)
            {
                for(const auto& elemIt : *combIt)
                    std::cout << *elemIt << " ";
                std::cout << std::endl;
            }
        }
    }
    {
        std::cout << "Last to first-------" << std::endl;
        typedef SetOfSets::const_reverse_iterator SetOfSetsCRIt;
        typedef combinations<SetOfSetsCRIt> Combinations;
        Combinations cmbs(data.crbegin(), data.crend());
        {
            std::cout << "Forward:" << std::endl;
            for(Combinations::const_iterator cmbIt = cmbs.begin();
                cmbIt != cmbs.end();
                ++cmbIt)
            {
                Combinations::Combination c = *cmbIt;
                std::reverse(c.begin(), c.end());
                for(const auto& it : c)
                    std::cout << *it << " ";
                std::cout << std::endl;
            }
        }
        {
            std::cout << "Reverse:" << std::endl;
            for(Combinations::const_reverse_iterator cmbIt = cmbs.crbegin();
                cmbIt != cmbs.crend();
                ++cmbIt)
            {
                Combinations::Combination c = *cmbIt;
                std::reverse(c.begin(), c.end());
                for(const auto& it : c)
                    std::cout << *it << " ";
                std::cout << std::endl;
            }
        }
    }
}
