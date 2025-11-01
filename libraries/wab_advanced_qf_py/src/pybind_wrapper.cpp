#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "equity.hpp"
#include "fx.hpp"
#include "rates.hpp"
#include "credit.hpp"
#include "random.hpp"
#include "linalg.hpp"

namespace py = pybind11;

PYBIND11_MODULE(wab_advanced_qf_py, m)
{
    m.doc() = "Python bindings for WAB Advanced Quantitative Finance Library";

    // ========== Equity Options ==========
    py::class_<EQ1>(m, "EQ1")
        .def(py::init<>(), "Default constructor")
        .def(py::init<double, double, double, double, double, int, int>(),
             py::arg("T"), py::arg("K"), py::arg("S0"), py::arg("sigma"),
             py::arg("r"), py::arg("N"), py::arg("M"),
             "Constructor with parameters: T (maturity), K (strike), S0 (spot), "
             "sigma (volatility), r (risk-free rate), N (time steps), M (simulations)")
        .def("get_premium", &EQ1::get_premium,
             "Calculate option premium using Monte Carlo simulation");

    py::class_<EQ2>(m, "EQ2")
        .def(py::init<>(), "Default constructor")
        .def(py::init<double, double, double, double, double, double, double, int, int>(),
             py::arg("T"), py::arg("r"), py::arg("S10"), py::arg("S20"),
             py::arg("sigma1"), py::arg("sigma2"), py::arg("rho"),
             py::arg("N"), py::arg("M"),
             "Constructor for two-asset option: T (maturity), r (risk-free rate), "
             "S10/S20 (initial spots), sigma1/sigma2 (volatilities), "
             "rho (correlation), N (time steps), M (simulations)")
        .def("get_premium", &EQ2::get_premium,
             "Calculate two-asset option premium using Monte Carlo simulation");

    // ========== FX Options ==========
    py::class_<result_data>(m, "FXResultData")
        .def(py::init<>(), "Default constructor")
        .def(py::init<double, double, double, std::vector<double>, std::vector<double>,
                      std::vector<double>, std::vector<double>,
                      matrix<double>, matrix<double>>(),
             py::arg("alpha"), py::arg("dtau"), py::arg("k"),
             py::arg("x"), py::arg("S"), py::arg("t"), py::arg("tau"),
             py::arg("u"), py::arg("v"))
        .def_readwrite("alpha", &result_data::alpha)
        .def_readwrite("dtau", &result_data::dtau)
        .def_readwrite("k", &result_data::k)
        .def_readwrite("x", &result_data::x)
        .def_readwrite("S", &result_data::S)
        .def_readwrite("t", &result_data::t)
        .def_readwrite("tau", &result_data::tau)
        .def_readwrite("u", &result_data::u, "Option value grid")
        .def_readwrite("v", &result_data::v, "Option value grid (alternative)");

    py::class_<FX1>(m, "FX1")
        .def(py::init<>(), "Default constructor")
        .def(py::init<double, double, double, double, double, double, double, int, int, bool>(),
             py::arg("T"), py::arg("K"), py::arg("S0"), py::arg("sigma"),
             py::arg("r"), py::arg("dt"), py::arg("dx"),
             py::arg("N"), py::arg("M"), py::arg("barrier") = false,
             "Constructor for FX option pricing using PDE: T (maturity), K (strike), "
             "S0 (spot), sigma (volatility), r (risk-free rate), dt (time step), "
             "dx (space step), N (time grid size), M (space grid size), barrier (bool)")
        .def("get_data_and_premium", &FX1::get_data_and_premium,
             "Calculate option premium and grid data using PDE solver")
        .def("set_barrier", &FX1::set_barrier, py::arg("barrier"),
             "Enable or disable barrier option pricing");

    // ========== Interest Rates ==========
    py::class_<IR_results>(m, "IRResults")
        .def(py::init<>(), "Default constructor")
        .def(py::init<std::vector<double>&, double>(),
             py::arg("datapoints"), py::arg("value"))
        .def_readwrite("datapoints", &IR_results::datapoints,
                      "LIBOR simulation datapoints")
        .def_readwrite("value", &IR_results::value,
                      "Present value of cap/floor");

    py::class_<IR>(m, "IR")
        .def(py::init<>(), "Default constructor")
        .def(py::init<double, double, double, double, double, int, int, bool>(),
             py::arg("notional"), py::arg("K"), py::arg("alpha"),
             py::arg("sigma"), py::arg("dT"), py::arg("N"), py::arg("M"),
             py::arg("cap") = false,
             "Constructor for interest rate cap/floor: notional, K (strike rate), "
             "alpha (mean reversion), sigma (volatility), dT (time step), "
             "N (time periods), M (simulations), cap (true for cap, false for floor)")
        .def(py::init<double, double, double, double, int, int, bool>(),
             py::arg("K"), py::arg("alpha"), py::arg("sigma"),
             py::arg("dT"), py::arg("N"), py::arg("M"), py::arg("cap"),
             "Constructor without notional parameter")
        .def("get_simulation_data", &IR::get_simulation_data,
             "Run LIBOR simulations and return results");

    // ========== Credit Risk ==========
    py::class_<CR1_results>(m, "CR1Results")
        .def(py::init<>(), "Default constructor")
        .def_readwrite("equity_payoff", &CR1_results::equity_payoff,
                      "Expected equity payoff")
        .def_readwrite("percentage_defaults", &CR1_results::percentage_defaults,
                      "Percentage of default scenarios");

    py::class_<CR2_results>(m, "CR2Results")
        .def(py::init<>(), "Default constructor")
        .def_readwrite("pv_premium_leg", &CR2_results::pv_premium_leg,
                      "Present value of premium leg")
        .def_readwrite("pv_default_leg", &CR2_results::pv_default_leg,
                      "Present value of default leg")
        .def_readwrite("cds_spread_in_bps", &CR2_results::cds_spread_in_bps,
                      "CDS spread in basis points");

    py::class_<CR1>(m, "CR1")
        .def(py::init<>(), "Default constructor")
        .def(py::init<double, double, double, double, double, int, int>(),
             py::arg("T"), py::arg("D"), py::arg("V0"), py::arg("sigma"),
             py::arg("r"), py::arg("N"), py::arg("M"),
             "Merton model for credit risk: T (maturity), D (debt), V0 (firm value), "
             "sigma (volatility), r (risk-free rate), N (time steps), M (simulations)")
        .def("get_payoff_and_defaults", &CR1::get_payoff_and_defaults,
             "Calculate equity payoff and default percentage");

    py::class_<CR2>(m, "CR2")
        .def(py::init<>(), "Default constructor")
        .def(py::init<double, int, double, double, double, double>(),
             py::arg("T"), py::arg("N"), py::arg("notional"),
             py::arg("r"), py::arg("h"), py::arg("rr"),
             "CDS pricing: T (maturity), N (payment periods), notional, "
             "r (risk-free rate), h (hazard rate), rr (recovery rate)")
        .def("get_pv_premium_and_default_legs_and_cds_spread",
             &CR2::get_pv_premium_and_default_legs_and_cds_spread,
             "Calculate PV of premium/default legs and CDS spread");

    // ========== Random Number Generation ==========
    py::class_<SampleBoxMuller>(m, "SampleBoxMuller")
        .def(py::init<>(), "Box-Muller random number generator")
        .def("__call__", &SampleBoxMuller::operator(),
             "Generate a standard normal random variable");

    // ========== Linear Algebra Utilities ==========
    m.def("matrix_creator", &matrix_creator,
          "Create a sample matrix (utility function)");
}
