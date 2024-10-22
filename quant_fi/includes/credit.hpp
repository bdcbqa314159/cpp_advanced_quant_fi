#pragma once

class CR1_results
{

public:
    CR1_results() = default;

    double equity_payoff{}, percentage_defaults{};
};

class CR2_results
{
public:
    CR2_results() {}

    double pv_premium_leg{}, pv_default_leg{}, cds_spread_in_bps{};
};

class CR1
{
public:
    CR1() = default;

    CR1(double T, double D, double V0, double sigma, double r, int N, int M) : T(T), D(D), V0(V0), sigma(sigma), r(r), N(N), M(M) {}

    CR1_results get_payoff_and_defaults() const
    {
        return find_payoff_and_defaults();
    }

private:
    double T{4}, D{70}, V0{100}, sigma{0.2}, r{0.05};
    int N{500}, M{1000};

    CR1_results find_payoff_and_defaults() const;
};

class CR2
{

public:
    CR2() = default;
    CR2(double T, int N, double notional, double r, double h, double rr) : T(T), N(N), notional(notional), r(r), h(h), rr(rr) {}

    CR2_results get_pv_premium_and_default_legs_and_cds_spread() const
    {
        return find_pv_premium_and_default_legs_and_cds_spread();
    }

private:
    double T{1}, notional{100}, r{0.05}, h{0.01}, rr{0.5};
    int N{4};
    CR2_results find_pv_premium_and_default_legs_and_cds_spread() const;
};