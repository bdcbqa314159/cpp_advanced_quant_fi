#pragma once
#include <vector>

template <class T>
using matrix = std::vector<std::vector<T>>;

template <class T>
inline void matrix_resize(T &u, size_t N, size_t M)
{
    u.resize(N);
    for (auto &row : u)
        row.resize(M);
}

matrix<double> matrix_creator();