#include "equity.hpp"
#include "random.hpp"
#include <algorithm>
#include <vector>
#include <cmath>

double EQ1::find_premium() const
{

    double sum_payoff{}, premium{};
    double dt = T / N;
    std::vector<double> S(N + 1);

    SampleBoxMuller normal;

    for (int j = 0; j < M; ++j)
    {
        S[0] = S0;
        for (int i = 0; i < N; ++i)
        {
            double epsilon = normal();
            S[i + 1] = S[i] * (1 + r * dt + sigma * std::sqrt(dt) * epsilon);
        }

        double diff = S[N] - K;
        sum_payoff += std::max(diff, 0.);
    }

    return std::exp(-r * T) * sum_payoff / M;
}

double EQ2::find_premium() const
{

    double sum_payoff{}, premium{};
    double dt = T / N;
    std::vector<double> S1(N + 1);
    std::vector<double> S2(N + 1);

    SampleBoxMuller normal;

    for (int j = 0; j < M; ++j)
    {
        S1[0] = S10;
        S2[0] = S20;
        for (int i = 0; i < N; ++i)
        {
            double epsilon1 = normal(), epsilon2 = normal();
            S1[i + 1] = S1[i] * (1 + r * dt + sigma1 * std::sqrt(dt) * epsilon1);
            S2[i + 1] = S2[i] * (1 + r * dt + sigma1 * std::sqrt(dt) * (epsilon1 * rho + std::sqrt(1 - rho * rho) * epsilon2));
        }

        sum_payoff += std::max(S1[N], S2[N]);
    }

    return std::exp(-r * T) * sum_payoff / M;
}