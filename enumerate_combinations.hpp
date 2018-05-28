#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include <iterator>
#include <vector>

// change combination to the next subsequent one
// increment last increment-able combination element
template <typename SetOfSetsIter, typename CombinationIter>
bool next_combination(
    CombinationIter combFirst,
    SetOfSetsIter dataFirst,
    SetOfSetsIter dataLast)
{
    for(; dataFirst != dataLast; ++dataFirst, ++combFirst)
    {
        if(++(*combFirst) != dataFirst->end())
            return true;
        *combFirst = dataFirst->begin();
    }
    return false;
}

// make combination from first elements of set's sets as a vector
template <typename SetOfSetsIter>
std::vector<
    typename std::iterator_traits<SetOfSetsIter>::value_type::const_iterator>
first_combination(SetOfSetsIter dataFirst, SetOfSetsIter dataLast)
{
    typedef typename std::iterator_traits<SetOfSetsIter>::value_type Set;
    std::vector<typename Set::const_iterator> comb;
    for(; dataFirst != dataLast; ++dataFirst)
        comb.push_back(dataFirst->cbegin());
    return comb;
}

#endif // COMBINATION_HPP
