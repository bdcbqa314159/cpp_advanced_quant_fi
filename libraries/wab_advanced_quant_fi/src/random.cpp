#include "random.hpp"
#include <cmath>

double SampleBoxMuller::operator()()
{
    do
    {
        x = 2. * rand() / RAND_MAX - 1;
        y = 2. * rand() / RAND_MAX - 1;

        norm2_sq = x * x + y * y;
    } while (norm2_sq >= 1.);

    result = x * std::sqrt(-2 * std::log(norm2_sq) / norm2_sq);
    return result;
}