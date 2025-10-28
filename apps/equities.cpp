#include "equity.hpp"
#include <iostream>

int main() {

  std::cout << "Hello from Advanced Quantitative Finance with C++" << std::endl;

  EQ1 eq1;

  double premium = eq1.get_premium();

  std::cout << "premium = " << premium << std::endl;

  EQ2 eq2;

  double premium_basket = eq2.get_premium();

  std::cout << "premium basket of stocks= " << premium_basket << std::endl;
}