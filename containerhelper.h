#pragma once
#include <algorithm>


template <typename Container>
bool contains(Container const& c, typename Container::const_reference v)
{
    return std::find(c.begin(), c.end(), v) != c.end();
}