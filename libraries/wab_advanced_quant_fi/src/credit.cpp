#include "credit.hpp"
#include "random.hpp"
#include <algorithm>
#include <vector>

CR1_results CR1::find_payoff_and_defaults() const
{
    std::vector<double> V(N + 1);
    double sumpayoff = 0;
    double dt = T / N;
    double default_count = 0.;

    SampleBoxMuller normal;

    for (int i = 0; i < M; i++)
    {
        V[0] = V0;

        for (int j = 0; j < N; j++)
        {
            double epsilon = normal();
            V[j + 1] = V[j] * (1 + r * dt + sigma * sqrt(dt) * epsilon);
        }

        sumpayoff += std::max(V[N] - D, 0.);

        if (V[N] > D)
        {
            default_count++;
        }
    }

    CR1_results results;
    results.equity_payoff = exp(-r * T) * (sumpayoff / M);
    results.percentage_defaults = 100 * default_count / M;

    return results;
}

CR2_results CR2::find_pv_premium_and_default_legs_and_cds_spread() const
{
    double pv_premium_leg = 0;
    double pv_default_leg = 0;
    double t = 0;
    double cds_spread = 0;

    int array_size = static_cast<int>(N * T + 1);

    std::vector<double> DF(array_size);
    std::vector<double> P(array_size);

    P[0] = 1.;
    double dt = T / N;

    for (int j = 1; j < array_size; j++)
    {
        t = j * dt;
        DF[j] = exp(-r * t);
        P[j] = exp(-h * t);

        pv_premium_leg += DF[j] * notional * dt * P[j];
        pv_default_leg += DF[j] * (1. - rr) * notional * (P[j - 1] - P[j]);
    }

    cds_spread = pv_default_leg / pv_premium_leg;

    CR2_results results;

    results.pv_premium_leg = pv_premium_leg;
    results.pv_default_leg = pv_default_leg;
    results.cds_spread_in_bps = cds_spread * 10000;

    return results;
}