#include "linalg.hpp"

matrix<double> matrix_creator()
{
    matrix<double> a;
    matrix_resize(a, 2, 2);
    return a;
}