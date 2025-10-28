#include "credit.hpp"
#include <iostream>

int main() {
  std::cout << "Hello from Advanced Quantitative Finance with C++\n";

  double T = 4., D = 70., V0 = 100., sigma = 0.2, r = 0.05;
  int N = 500, M = 10000;

  CR1 cr1(T, D, V0, sigma, r, N, M);

  CR1_results results = cr1.get_payoff_and_defaults();

  std::cout << "Equity payoff E(0) = " << results.equity_payoff << "\n";
  std::cout << "percentage defaults = " << results.percentage_defaults << "\n";

  std::cout << "Working with a simple CDS" << "\n";

  CR2 cr2(1, 4, 100, 0.05, 0.01, 0.5);

  CR2_results results2 = cr2.get_pv_premium_and_default_legs_and_cds_spread();

  std::cout << "PV premium leg = " << results2.pv_premium_leg << "\n";
  std::cout << "PV default leg = " << results2.pv_default_leg << "\n";
  std::cout << "PV spread in bps = " << results2.cds_spread_in_bps << "\n";

  return 0;
}