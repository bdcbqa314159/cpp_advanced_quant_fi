# WAB Advanced Quantitative Finance - Python Bindings

This directory contains Python bindings for the WAB Advanced Quantitative Finance C++ library.

## Overview

The Python bindings provide access to the following quantitative finance modules:

- **Equity Options**: Single-asset and basket option pricing using Monte Carlo simulation
- **Credit Risk**: Merton model for corporate debt and CDS pricing
- **Interest Rates**: LIBOR simulations, interest rate swaps, caps and floors
- **Forex Options**: FX option pricing using PDE solvers with barrier option support
- **Random Number Generation**: Box-Muller sampling for Monte Carlo simulations

## Building the Python Module

The Python module is built as part of the main CMake build process:

```bash
# From the repository root
mkdir -p build
cd build
cmake ..
make
make install
```

## Setting up PYTHONPATH

After installation, add the module to your Python path:

```bash
export PYTHONPATH=/path/to/install/python:$PYTHONPATH
```

Replace `/path/to/install` with your actual installation prefix (default is usually the build directory).

## Running Tests

### Option 1: Using pytest

Install test dependencies from the project root:

```bash
pip install -r requirements.txt
```

Run all tests with pytest from the project root:

```bash
# Make sure PYTHONPATH is set correctly first
pytest tests/test_quantitative_finance.py -v
```

Run with coverage report:

```bash
pytest tests/test_quantitative_finance.py -v --cov=wab_advanced_qf_py
```

### Option 2: Direct Python execution

You can also run the tests directly without pytest:

```bash
python tests/test_quantitative_finance.py
```

This will execute all test cases and print detailed results.

## Test Coverage

The test suite mirrors the functionality from the C++ applications:

### Equity Options Tests (apps/equities.cpp)

- `test_eq1_default_constructor`: Tests single-asset option with defaults
- `test_eq1_custom_parameters`: Tests with custom parameters
- `test_eq2_default_constructor`: Tests basket option with defaults
- `test_eq2_custom_parameters`: Tests basket with custom parameters

### Credit Risk Tests (apps/credit_risk.cpp)

- `test_cr1_default_constructor`: Tests Merton model with defaults
- `test_cr1_custom_parameters`: Tests with specific parameters (T=4, D=70, etc.)
- `test_cr2_default_constructor`: Tests CDS pricing with defaults
- `test_cr2_custom_parameters`: Tests with specific CDS parameters

### Interest Rates Tests (apps/interest_rates.cpp)

- `test_ir_default_constructor`: Tests IR with defaults
- `test_ir_swap_pricing`: Tests interest rate swap with notional=1e6
- `test_ir_cap_pricing`: Tests interest rate cap pricing

### Forex Options Tests (apps/forex.cpp)

- `test_fx1_default_constructor`: Tests vanilla FX option
- `test_fx1_vanilla_option`: Tests standard European option
- `test_fx1_barrier_option`: Tests with barrier enabled
- `test_fx1_custom_parameters`: Tests with custom grid parameters

### Random Number Generation Tests

- `test_box_muller_sampling`: Tests Box-Muller RNG with statistical validation

## Example Usage

```python
import wab_advanced_qf_py as qf

# Price a single-asset equity option
eq1 = qf.EQ1(T=1.0, K=100.0, S0=100.0, sigma=0.1, r=0.05, N=500, M=10000)
premium = eq1.get_premium()
print(f"Option premium: {premium}")

# Price a CDS
cr2 = qf.CR2(T=1.0, N=4, notional=100.0, r=0.05, h=0.01, rr=0.5)
results = cr2.get_pv_premium_and_default_legs_and_cds_spread()
print(f"CDS spread: {results.cds_spread_in_bps} bps")

# Run interest rate simulations
ir = qf.IR(notional=1e6, K=0.04, alpha=0.25, sigma=0.15, dT=0.25, N=3, M=1000)
results = ir.get_simulation_data()
print(f"IRS PV: {results.value}")

# Price an FX option with barrier
fx = qf.FX1()
fx.set_barrier(True)
result = fx.get_data_and_premium()
print(f"FX option grid computed with alpha={result.alpha}")
```

## Troubleshooting

### Module not found error

If you get `ModuleNotFoundError: No module named 'wab_advanced_qf_py'`:

1. Check that the build completed successfully
2. Verify the module exists in the install directory
3. Set PYTHONPATH correctly:

   ```bash
   export PYTHONPATH=/path/to/install/python:$PYTHONPATH
   ```

### Import errors

If you see errors about missing C++ libraries, ensure that:

- The C++ library was built successfully
- All dependencies are properly linked
- You're using a compatible Python version (3.7+)

## Module Documentation

For detailed parameter information, use Python's help:

```python
import wab_advanced_qf_py as qf
help(qf.EQ1)
help(qf.CR2)
help(qf.IR)
help(qf.FX1)
```

Each class constructor and method includes detailed docstrings explaining parameters and return values.
