"""
Comprehensive test suite for WAB Advanced Quantitative Finance Library

This test suite mirrors the functionality tested in the C++ applications:
- apps/equities.cpp
- apps/credit_risk.cpp
- apps/interest_rates.cpp
- apps/forex.cpp

Usage:
    Run from the installation directory or with PYTHONPATH set:
    python test_quantitative_finance.py
"""

import sys
from pathlib import Path

# Try to add the installation path automatically
install_dir = Path(__file__).parent.parent / "install" / "python"
if install_dir.exists():
    sys.path.insert(0, str(install_dir))

# Import the C++ Python bindings module
try:
    import wab_advanced_qf_py as qf
except ImportError as e:
    print(f"Error importing wab_advanced_qf: {e}")
    print("\nMake sure the module is built and accessible.")
    print("Options:")
    print("  1. Run from build/python directory")
    print("  2. Set PYTHONPATH: export PYTHONPATH=/path/to/build/python:$PYTHONPATH")
    print(f"  3. Install and the script will auto-detect from: {install_dir}")
    sys.exit(1)


class TestEquityOptions:
    """Test suite for Equity Options (mirrors apps/equities.cpp)"""

    def test_eq1_default_constructor(self):
        """Test EQ1 with default constructor"""
        eq1 = qf.EQ1()
        premium = eq1.get_premium()

        # Premium should be a positive number
        assert isinstance(premium, float)
        assert premium > 0
        print(f"EQ1 premium (default params) = {premium}")

    def test_eq1_custom_parameters(self):
        """Test EQ1 with custom parameters"""
        # Parameters: T, K, S0, sigma, r, N, M
        eq1 = qf.EQ1(1.0, 100.0, 100.0, 0.1, 0.05, 500, 10000)
        premium = eq1.get_premium()

        assert isinstance(premium, float)
        assert premium > 0
        print(f"EQ1 premium (custom params) = {premium}")

    def test_eq2_default_constructor(self):
        """Test EQ2 basket option with default constructor"""
        eq2 = qf.EQ2()
        premium_basket = eq2.get_premium()

        assert isinstance(premium_basket, float)
        assert premium_basket > 0
        print(f"EQ2 premium basket of stocks (default params) = {premium_basket}")

    def test_eq2_custom_parameters(self):
        """Test EQ2 with custom parameters"""
        # Parameters: T, r, S10, S20, sigma1, sigma2, rho, N, M
        eq2 = qf.EQ2(1.0, 0.05, 120.0, 100.0, 0.1, 0.15, 0.5, 300, 1000)
        premium_basket = eq2.get_premium()

        assert isinstance(premium_basket, float)
        assert premium_basket > 0
        print(f"EQ2 premium basket (custom params) = {premium_basket}")


class TestCreditRisk:
    """Test suite for Credit Risk (mirrors apps/credit_risk.cpp)"""

    def test_cr1_default_constructor(self):
        """Test CR1 Merton model with default constructor"""
        cr1 = qf.CR1()
        results = cr1.get_payoff_and_defaults()

        assert isinstance(results, qf.CR1Results)
        assert hasattr(results, 'equity_payoff')
        assert hasattr(results, 'percentage_defaults')
        assert results.equity_payoff >= 0
        assert 0 <= results.percentage_defaults <= 100

        print(f"CR1 (default) - Equity payoff E(0) = {results.equity_payoff}")
        print(f"CR1 (default) - Percentage defaults = {results.percentage_defaults}%")

    def test_cr1_custom_parameters(self):
        """Test CR1 with custom parameters (mirrors credit_risk.cpp)"""
        # Parameters from credit_risk.cpp: T=4, D=70, V0=100, sigma=0.2, r=0.05, N=500, M=10000
        T = 4.0
        D = 70.0
        V0 = 100.0
        sigma = 0.2
        r = 0.05
        N = 500
        M = 10000

        cr1 = qf.CR1(T, D, V0, sigma, r, N, M)
        results = cr1.get_payoff_and_defaults()

        assert isinstance(results, qf.CR1Results)
        assert results.equity_payoff >= 0
        assert 0 <= results.percentage_defaults <= 100

        print(f"CR1 - Equity payoff E(0) = {results.equity_payoff}")
        print(f"CR1 - Percentage defaults = {results.percentage_defaults}%")

    def test_cr2_default_constructor(self):
        """Test CR2 CDS pricing with default constructor"""
        cr2 = qf.CR2()
        results = cr2.get_pv_premium_and_default_legs_and_cds_spread()

        assert isinstance(results, qf.CR2Results)
        assert hasattr(results, 'pv_premium_leg')
        assert hasattr(results, 'pv_default_leg')
        assert hasattr(results, 'cds_spread_in_bps')

        print(f"CR2 (default) - PV premium leg = {results.pv_premium_leg}")
        print(f"CR2 (default) - PV default leg = {results.pv_default_leg}")
        print(f"CR2 (default) - CDS spread in bps = {results.cds_spread_in_bps}")

    def test_cr2_custom_parameters(self):
        """Test CR2 with custom parameters (mirrors credit_risk.cpp)"""
        # Parameters from credit_risk.cpp: T=1, N=4, notional=100, r=0.05, h=0.01, rr=0.5
        T = 1.0
        N = 4
        notional = 100.0
        r = 0.05
        h = 0.01
        rr = 0.5

        cr2 = qf.CR2(T, N, notional, r, h, rr)
        results = cr2.get_pv_premium_and_default_legs_and_cds_spread()

        assert isinstance(results, qf.CR2Results)
        assert results.pv_premium_leg > 0
        assert results.pv_default_leg > 0
        assert results.cds_spread_in_bps > 0

        print("Working with a simple CDS")
        print(f"CR2 - PV premium leg = {results.pv_premium_leg}")
        print(f"CR2 - PV default leg = {results.pv_default_leg}")
        print(f"CR2 - CDS spread in bps = {results.cds_spread_in_bps}")


class TestInterestRates:
    """Test suite for Interest Rates (mirrors apps/interest_rates.cpp)"""

    def test_ir_default_constructor(self):
        """Test IR with default constructor"""
        ir = qf.IR()
        results = ir.get_simulation_data()

        assert isinstance(results, qf.IRResults)
        assert hasattr(results, 'datapoints')
        assert hasattr(results, 'value')
        assert len(results.datapoints) > 0

        print(f"IR (default) - Number of simulations: {len(results.datapoints)}")
        print(f"IR (default) - IRS PV = {results.value}")

    def test_ir_swap_pricing(self):
        """Test IR swap pricing (mirrors interest_rates.cpp first example)"""
        # Parameters from interest_rates.cpp
        notional = 1e6
        K = 0.04
        alpha = 0.25
        sigma = 0.15
        dT = 0.25
        N = 3
        M = 1000

        ir1 = qf.IR(notional, K, alpha, sigma, dT, N, M)
        results = ir1.get_simulation_data()

        assert isinstance(results, qf.IRResults)
        assert len(results.datapoints) > 0

        # Print first few simulations
        print("\nInterest Rate Swap Simulations:")
        for nsim, value in enumerate(results.datapoints):
            print(f"simIRS[{nsim}] = {value}")

        print(f"IRS PV = {results.value}")

        assert isinstance(results.value, float)

    def test_ir_cap_pricing(self):
        """Test IR cap pricing (mirrors interest_rates.cpp second example)"""
        # Parameters from interest_rates.cpp for cap
        K = 0.05
        alpha = 0.5
        sigma = 0.15
        dT = 0.5
        N = 4
        M = 1000
        cap = True

        ir2 = qf.IR(K, alpha, sigma, dT, N, M, cap)
        results2 = ir2.get_simulation_data()

        assert isinstance(results2, qf.IRResults)
        assert len(results2.datapoints) > 0

        print("\nWorking with a cap")
        print("Interest Rate Cap Simulations:")
        for nsim, value in enumerate(results2.datapoints):
            print(f"simCap[{nsim}] = {value}")

        print(f"IRS cap PV = {results2.value}")

        assert isinstance(results2.value, float)


class TestForexOptions:
    """Test suite for Forex Options (mirrors apps/forex.cpp)"""

    def test_fx1_default_constructor(self):
        """Test FX1 with default constructor"""
        fx = qf.FX1()
        result = fx.get_data_and_premium()

        assert isinstance(result, qf.FXResultData)
        assert hasattr(result, 'alpha')
        assert hasattr(result, 'dtau')
        assert hasattr(result, 'k')
        assert hasattr(result, 'x')
        assert hasattr(result, 'S')
        assert hasattr(result, 't')
        assert hasattr(result, 'tau')
        assert hasattr(result, 'u')
        assert hasattr(result, 'v')

        print(f"\nFX1 (default, no barrier):")
        print(f"  alpha = {result.alpha}")
        print(f"  dtau = {result.dtau}")
        print(f"  k = {result.k}")
        print(f"  x grid size = {len(result.x)}")
        print(f"  S grid size = {len(result.S)}")
        print(f"  t grid size = {len(result.t)}")
        print(f"  tau grid size = {len(result.tau)}")
        print(f"  u matrix shape = {len(result.u)} x {len(result.u[0]) if result.u else 0}")
        print(f"  v matrix shape = {len(result.v)} x {len(result.v[0]) if result.v else 0}")

    def test_fx1_vanilla_option(self):
        """Test FX1 vanilla option (mirrors forex.cpp first example)"""
        fx = qf.FX1()
        result = fx.get_data_and_premium()

        assert isinstance(result, qf.FXResultData)
        print(f"\nFX1 Vanilla Option Results:")
        print(f"  Premium calculation completed")
        print(f"  Grid parameters: alpha={result.alpha}, dtau={result.dtau}, k={result.k}")

    def test_fx1_barrier_option(self):
        """Test FX1 barrier option (mirrors forex.cpp second example)"""
        fx1 = qf.FX1()
        fx1.set_barrier(True)
        result1 = fx1.get_data_and_premium()

        assert isinstance(result1, qf.FXResultData)
        print(f"\nFX1 Barrier Option Results:")
        print(f"  Barrier option calculation completed")
        print(f"  Grid parameters: alpha={result1.alpha}, dtau={result1.dtau}, k={result1.k}")

    def test_fx1_custom_parameters(self):
        """Test FX1 with custom parameters"""
        # Parameters: T, K, S0, sigma, r, dt, dx, N, M, barrier
        T = 0.5
        K = 75.0
        S0 = 75.0
        sigma = 0.3
        r = 0.05
        dt = 0.1
        dx = 0.5
        N = 5
        M = 6
        barrier = False

        fx = qf.FX1(T, K, S0, sigma, r, dt, dx, N, M, barrier)
        result = fx.get_data_and_premium()

        assert isinstance(result, qf.FXResultData)
        assert result.alpha > 0
        assert result.dtau > 0
        print(f"\nFX1 Custom Parameters:")
        print(f"  Successfully computed with T={T}, K={K}, S0={S0}")


class TestRandomNumberGeneration:
    """Test suite for Random Number Generation utilities"""

    def test_box_muller_sampling(self):
        """Test Box-Muller random number generator"""
        rng = qf.SampleBoxMuller()

        # Generate some samples
        samples = [rng() for _ in range(1000)]

        assert len(samples) == 1000
        assert all(isinstance(s, float) for s in samples)

        # Basic statistical checks (mean should be close to 0, std close to 1)
        mean = sum(samples) / len(samples)
        variance = sum((x - mean)**2 for x in samples) / len(samples)
        std_dev = variance ** 0.5

        print(f"\nBox-Muller RNG Statistics (1000 samples):")
        print(f"  Mean: {mean:.4f} (expected: 0.0)")
        print(f"  Std Dev: {std_dev:.4f} (expected: 1.0)")

        # Allow some tolerance for random samples
        assert abs(mean) < 0.1, f"Mean {mean} too far from 0"
        assert abs(std_dev - 1.0) < 0.1, f"Std dev {std_dev} too far from 1.0"


def test_module_import():
    """Test that the module can be imported and has expected attributes"""
    assert hasattr(qf, 'EQ1')
    assert hasattr(qf, 'EQ2')
    assert hasattr(qf, 'CR1')
    assert hasattr(qf, 'CR2')
    assert hasattr(qf, 'IR')
    assert hasattr(qf, 'FX1')
    assert hasattr(qf, 'SampleBoxMuller')
    print("\nAll expected classes are available in the module")


if __name__ == "__main__":
    """Run tests manually without pytest"""
    print("=" * 80)
    print("Running WAB Advanced Quantitative Finance Tests")
    print("=" * 80)

    # Test module import
    print("\n" + "=" * 80)
    print("MODULE IMPORT TEST")
    print("=" * 80)
    test_module_import()

    # Equity Options Tests
    print("\n" + "=" * 80)
    print("EQUITY OPTIONS TESTS")
    print("=" * 80)
    equity_tests = TestEquityOptions()
    equity_tests.test_eq1_default_constructor()
    equity_tests.test_eq1_custom_parameters()
    equity_tests.test_eq2_default_constructor()
    equity_tests.test_eq2_custom_parameters()

    # Credit Risk Tests
    print("\n" + "=" * 80)
    print("CREDIT RISK TESTS")
    print("=" * 80)
    credit_tests = TestCreditRisk()
    credit_tests.test_cr1_default_constructor()
    credit_tests.test_cr1_custom_parameters()
    credit_tests.test_cr2_default_constructor()
    credit_tests.test_cr2_custom_parameters()

    # Interest Rates Tests
    print("\n" + "=" * 80)
    print("INTEREST RATES TESTS")
    print("=" * 80)
    ir_tests = TestInterestRates()
    ir_tests.test_ir_default_constructor()
    ir_tests.test_ir_swap_pricing()
    ir_tests.test_ir_cap_pricing()

    # Forex Options Tests
    print("\n" + "=" * 80)
    print("FOREX OPTIONS TESTS")
    print("=" * 80)
    fx_tests = TestForexOptions()
    fx_tests.test_fx1_default_constructor()
    fx_tests.test_fx1_vanilla_option()
    fx_tests.test_fx1_barrier_option()
    fx_tests.test_fx1_custom_parameters()

    # Random Number Generation Tests
    print("\n" + "=" * 80)
    print("RANDOM NUMBER GENERATION TESTS")
    print("=" * 80)
    rng_tests = TestRandomNumberGeneration()
    rng_tests.test_box_muller_sampling()

    print("\n" + "=" * 80)
    print("ALL TESTS COMPLETED SUCCESSFULLY!")
    print("=" * 80)
