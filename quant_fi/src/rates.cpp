#include "rates.hpp"
#include "random.hpp"
#include "linalg.hpp"

IR_results IR::run_LIBOR_simulations() const
{
    matrix<double> L;
    matrix_resize(L, N + 1, N + 1);
    matrix<double> D;
    matrix_resize(D, N + 2, N + 2);

    std::vector<double> dW(N + 1);
    std::vector<double> FV(N + 2);

    std::vector<double> FVprime(N + 2);
    std::vector<double> V(M);

    SampleBoxMuller normal;

    double df_prod = 1.;
    double drift_sum = 0.;
    double sumPV = 0.;
    double PV = 0.;

    double spot_init = 0.05;

    for (int i = 0; i < N + 1; i++)
        L[i][0] = spot_init;

    dW[0] = 0.;

    for (int nsim = 0; nsim < M; nsim++)
    {
        for (int j = 1; j < N + 1; j++)
            dW[j] = sqrt(dT) * normal();

        for (int n = 0; n < N; n++)
        {
            for (int i = n + 1; i < N + 1; i++)
            {
                drift_sum = 0.;
                for (int k = i + 1; k < N + 1; k++)
                    drift_sum += (alpha * sigma * L[k][n]) / (1 + alpha * L[k][n]);

                L[i][n + 1] = L[i][n] * exp((-drift_sum * sigma - 0.5 * sigma * sigma) * dT + sigma * dW[n + 1]);
            }
        }

        for (int n = 0; n < N + 1; n++)
        {
            for (int i = n + 1; i < N + 2; i++)
            {
                df_prod = 1.;
                for (int k = n; k < i; k++)
                {
                    df_prod *= 1 / (1 + alpha * L[k][n]);
                }

                D[i][n] = df_prod;
            }
        }

        double diff(0.);
        V[nsim] = 0.;

        for (int i = 1; i < N + 2; i++)
        {

            if (cap)
            {
                diff = L[i - 1][i - 1] - K;
                FV[i] = std::max(diff, 0.);
            }

            else
            {
                diff = notional * alpha * (L[i - 1][i - 1] - K);
                FV[i] = diff;
            }

            FVprime[i] = FV[i] * D[i][i - 1] / D[N + 1][i - 1];

            if (cap)
            {
                V[nsim] += FVprime[i];
            }

            else
            {
                V[nsim] += FVprime[i] * D[i][0];
            }
        }
    }

    sumPV = 0.;

    for (int nsim = 0; nsim < M; nsim++)
        sumPV += V[nsim];

    if (cap)
    {
        PV = D[N + 1][0] * sumPV / M;
    }
    else
    {
        PV = sumPV / M;
    }

    IR_results results(V, PV);

    return results;
}