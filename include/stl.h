#ifndef STL_H
#define STL_H


#include <vector>
#include <algorithm>
#include <numeric>
#include <string>



inline void initial_vector_with_3_mutiplies(std::vector<int>& v, size_t size)
{
    v.resize(size);
    int n {0};
    std::generate(v.begin(), v.end(), [&n](){return n+=3;});
}


inline int count_unique_above(const std::vector<int>& v, const int& n)
{
    std::set<int, std::less<>> myset {v.begin(), v.end()};
    return std::count_if(myset.begin(), myset.end(), [&n](const int& a){return a > n;});
}

inline std::string vector_to_string(const std::vector<int>& v, const char& separator)
{
    auto dash_fold = [separator](std::string a, int b)
    {
        return std::move(a) + separator + std::to_string(b);
    };

    return std::accumulate(std::next(v.rbegin()), v.rend(), std::to_string(v.back()), dash_fold);
}

#endif //STL_H