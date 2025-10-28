#pragma once

class EQ1
{
public:
    EQ1() = default;
    EQ1(double T, double K, double S0, double sigma, double r, int N, int M) : T(T), K(K), S0(S0), sigma(sigma), r(r), N(N), M(M) {}

    double get_premium() const
    {
        return find_premium();
    }

private:
    double T{1}, K{100}, S0{100}, sigma{0.1}, r{0.05};
    int N{500}, M{10000};
    double find_premium() const;
};

class EQ2
{
public:
    EQ2() = default;
    EQ2(double T, double r, double S10, double S20, double sigma1, double sigma2, double rho, int N, int M) : T(T), r(r), S10(S10), S20(S20), sigma1(sigma1), sigma2(sigma2), rho(rho), N(N), M(M) {}

    double get_premium() const
    {
        return find_premium();
    }

private:
    double T{1}, r{0.05}, S10{120}, S20{100}, sigma1{0.1}, sigma2{0.15}, rho{0.5};
    int N{300}, M{1000};

    double find_premium() const;
};