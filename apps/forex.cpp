#include "fx.hpp"
#include <iostream>

int main() {

  std::cout << "Hello from Advanced Quantitative Finance with C++\n";

  FX1 fx;

  auto result = fx.get_data_and_premium();

  std::cout << result << "\n";

  FX1 fx1;
  fx1.set_barrier(true);

  auto result1 = fx1.get_data_and_premium();

  std::cout << result1 << "\n";
}