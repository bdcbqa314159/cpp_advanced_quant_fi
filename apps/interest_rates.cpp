#include "rates.hpp"
#include <iostream>

int main() {
  std::cout << "Hello from Advanced Quantitative Finance with C++\n";

  double notional = 1e6;
  double K = 0.04;
  double alpha = 0.25;
  double sigma = 0.15;
  double dT = 0.25;

  int N = 3;
  int M = 1000;

  IR ir1(notional, K, alpha, sigma, dT, N, M);

  auto results = ir1.get_simulation_data();

  auto sz = results.datapoints.size();
  for (int nsim = 0; nsim < sz; nsim++)
    std::cout << "simIRS[" << nsim << "] = " << results.datapoints[nsim]
              << "\n";

  std::cout << "IRS PV = " << results.value << "\n";

  std::cout << "Working with a cap" << "\n";

  IR ir2(0.05, 0.5, 0.15, 0.5, 4, 1000, true);
  auto results2 = ir2.get_simulation_data();
  auto sz2 = results2.datapoints.size();
  for (int nsim = 0; nsim < sz2; nsim++)
    std::cout << "simIRS[" << nsim << "] = " << results2.datapoints[nsim]
              << "\n";

  std::cout << "IRS cap PV = " << results2.value << "\n";

  return 0;
}