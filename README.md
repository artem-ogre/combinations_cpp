# Enumerate combinations
Enumerate all combinations of elements from container-of-containers. Compatible with c++98.

## Example

```c++
#include <iostream>

#include "enumerate_combinations.hpp"

int main(int /*argc*/, char* /*argv*/ [])
{
    typedef std::vector<int> Set;
    typedef std::vector<Set> SetOfSets;
    const SetOfSets data = {{2, 4}, {1, 3, 8}, {7, 5}};
    
    std::cout << "First to last:" << std::endl;
    std::vector<Set::const_iterator> comb = first_combination(data.cbegin(), data.cend());
    do
    {
        for(const auto& it : comb)
            std::cout << *it << " ";
        std::cout << std::endl;
    } while(next_combination(comb.begin(), data.cbegin(), data.cend()));
    
    std::cout << "\nLast to first:" << std::endl;
    comb = first_combination(data.cbegin(), data.cend());
    do
    {
        for(const auto& it : comb)
            std::cout << *it << " ";
        std::cout << std::endl;
    } while(next_combination(comb.rbegin(), data.crbegin(), data.crend()));
}
```
