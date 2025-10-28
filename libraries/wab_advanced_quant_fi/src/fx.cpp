#include "fx.hpp"
#include <cmath>
#include <algorithm>
#include <iomanip>

result_data FX1::evaluate_data_and_premium() const
{
    double dtau{}, alpha{}, k{};

    vec t(M), tau(M), S(N), x(N);

    matrix<double> u, v;
    matrix_resize(u, N, M);
    matrix_resize(v, N, M);

    double sigma_square = sigma * sigma;
    double dx_square = dx * dx;

    dtau = dt * 0.5 * sigma_square;
    alpha = dtau / dx_square;
    k = r / (0.5 * sigma_square);

    double xmin = -1, xmax = 1;

    // MESH:
    for (int i = 0; i < N; i++)
    {
        x[i] = xmin + i * dx;
        S[i] = K * std::exp(x[i]);
    }

    for (int j = 0; j < M; j++)
    {
        t[j] = j * dt;
        tau[j] = (T - t[j]) / (0.5 * sigma_square);
    }

    // INITIAL CONDITION
    for (int i = 0; i < N; i++)
    {
        u[i][0] = std::max(std::exp(0.5 * (k + 1) * x[i]) - std::exp(0.5 * (k - 1) * x[i]), 0.);
    }

    // BOUNDARY CONDITION

    for (int j = 1; j < M; j++)
    {
        u[0][j] = 0.;

        if (barrier)
            u[N - 1][j] = 0.;
        else
            u[N - 1][j] = u[N - 1][0];
    }

    // COMPUTE FORWARD DIFFERENCE

    for (int j = 0; j < M - 1; j++)
    {
        for (int i = 1; i < N - 1; i++)
        {
            u[i][j + 1] = alpha * u[i + 1][j] + (1 - 2 * alpha) * u[i][j] + alpha * u[i - 1][j];
        }
    }

    // TRANSFORM SOLUTION FROM X TO S COORDINATES

    for (int j = 0; j < M; j++)
    {
        for (int i = 1; i < N; i++)
        {
            v[i][j] = std::pow(K, (0.5 * (1 + k))) * std::pow(S[i], (0.5 * (1 - k))) * std::exp((k + 1) * (k + 1) * sigma_square * (T - t[i]) / 8.) * u[i][j];
        }
    }

    result_data result(alpha, dtau, k, x, S, t, tau, u, v);

    return result;
}

std::ostream &operator<<(std::ostream &os, const result_data &rs)
{
    int M{}, N{};

    N = rs.u.size();

    if (N)
        M = rs.u[0].size();

    os << std::setw(10) << " dtau = " << rs.dtau << "\n";
    os << std::setw(10) << " alpha = " << rs.alpha << "\n";
    os << std::setw(10) << " k = " << rs.k << "\n";

    os << "\n"
       << "...... x and tau grids ........" << "\n"
       << "\n";

    for (int i = 0; i < N; i++)
    {
        os << std::setw(5) << "x " << rs.x[i] << "\n";
        os << std::setw(5) << "S " << rs.S[i] << "\n";
    }

    for (int j = 0; j < M; j++)
    {
        os << std::setw(5) << "t " << rs.t[j] << "\n";
        os << std::setw(5) << "tau " << rs.tau[j] << "\n";
    }

    for (int i = 0; i < N; i++)
    {
        os << std::setw(5) << "i " << i << std::setw(5) << "u " << rs.u[i][0] << "\n";
    }

    os << "\n"
       << "..... bcs ........" << "\n"
       << "\n";

    for (int j = 1; j < M; j++)
    {
        os << std::setw(5) << "j " << j << std::setw(12) << "u[0][j] " << rs.u[0][j] << "\n";
        os << std::setw(5) << "j " << j << std::setw(12) << "u[N-1][j] " << rs.u[N - 1][j] << "\n";
    }

    os << "\n"
       << "..... u and v ........" << "\n"
       << "\n";

    for (int j = 0; j < M; j++)
    {
        for (int i = 0; i < N; i++)
        {
            os << std::setw(5) << "i= " << i << ", j= " << j << std::setw(11) << " v[i][j] " << rs.v[i][j] << "\n";
        }
    }

    os << "\n"
       << "premium = " << rs.v[N / 2][M - 1] << "\n";

    return os;
}