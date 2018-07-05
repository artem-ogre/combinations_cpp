# Enumerate combinations
A custom container with a bi-directional custom iterator for iterating over all combinations of elements from multiple sets.

Some implementation details:
- The container does not store all the combinations
- Combinations are calculated on the fly when iterator is incremented or decremented
- Combination is represented as a vector of iterators: one for each set
- When combinations iterator is dereferenced or arrow operator is called, combination is returned by value to avoid dangling
- c++98 compatible


### Table of Contents  
- [Synopsis](#synopsis)  
- [Example](#example)  
- [Example output](#example-output)  


### Synopsis
```c++
// Precondition: all sets between iterators should be non-empty:
// contain at least 1 element
template <typename SetsIter>
class combinations
{
public:
    typedef combinations<SetsIter> Combinations_type;
    typedef typename std::iterator_traits<SetsIter>::value_type Set;
    typedef typename std::vector<typename Set::const_iterator> Combination;

    typedef Combination value_type;
    typedef long long difference_type;
    typedef size_t size_type;

    class const_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef typename Combinations_type::difference_type difference_type;
        typedef typename Combinations_type::value_type value_type;
        typedef const Combination reference;
        typedef const Combination pointer;

        const_iterator() {}
        const_iterator(const const_iterator& other);
        const_iterator(SetsIter first, SetsIter last, Combination combination);
        static const_iterator make_begin(const SetsIter first, const SetsIter last);
        static const_iterator make_end(const SetsIter first, const SetsIter last);
        ~const_iterator() {}
        const_iterator& operator=(const const_iterator other);
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
        const_iterator& operator++();
        const_iterator& operator--();
        Combination operator*() const;
        Combination operator->() const;
        friend void swap(const_iterator& first, const_iterator& second);
        void swap(Combinations_type other);
    };

    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    combinations();
    combinations(SetsIter first, SetsIter last);
    combinations(const combinations<SetsIter>& other);
    ~combinations();
    combinations& operator=(const combinations<SetsIter>& other);
    bool operator==(const combinations<SetsIter>& other) const;
    bool operator!=(const combinations<SetsIter>& other) const;
    const_iterator cbegin() const;
    const_iterator begin() const;
    const_iterator cend() const;
    const_iterator end() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crend() const;
    const_reverse_iterator rend() const;
    friend void swap(combinations<SetsIter>& first, combinations<SetsIter>& second);
    void swap(combinations<SetsIter> other);
    size_type size() const;
    size_type max_size() const;
    bool empty() const;
};

template <typename Sets>
combinations<typename Sets::const_iterator> make_combinations(const Sets& data);
```

### Example

```c++
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
```

### Example output
```
First to last-------
Forward:
2 1 7 
4 1 7 
2 3 7 
4 3 7 
2 8 7 
4 8 7 
2 1 5 
4 1 5 
2 3 5 
4 3 5 
2 8 5 
4 8 5 
Reverse:
4 8 5 
2 8 5 
4 3 5 
2 3 5 
4 1 5 
2 1 5 
4 8 7 
2 8 7 
4 3 7 
2 3 7 
4 1 7 
2 1 7 
Last to first-------
Forward:
2 1 7 
2 1 5 
2 3 7 
2 3 5 
2 8 7 
2 8 5 
4 1 7 
4 1 5 
4 3 7 
4 3 5 
4 8 7 
4 8 5 
Reverse:
4 8 5 
4 8 7 
4 3 5 
4 3 7 
4 1 5 
4 1 7 
2 8 5 
2 8 7 
2 3 5 
2 3 7 
2 1 5 
2 1 7 
```
