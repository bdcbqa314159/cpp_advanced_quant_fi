# Advanced Quantitative Finance with C++

A comprehensive C++ library for quantitative finance modeling with Python bindings. This repository belongs to my collection of coding along with a book.

## Overview

This project implements advanced quantitative finance models and algorithms in C++, covering:

- **Equity Options**: Single-asset and basket option pricing using Monte Carlo simulation
- **Credit Risk**: Merton model for corporate debt valuation and CDS pricing
- **Interest Rates**: LIBOR simulations, interest rate swaps, caps and floors
- **Forex Options**: FX option pricing using PDE solvers with barrier option support
- **Random Number Generation**: Box-Muller sampling for Monte Carlo simulations

## Project Structure

```
cpp_advanced_quant_fi/
├── apps/                          # C++ executable applications
│   ├── equities.cpp              # Equity options examples
│   ├── credit_risk.cpp           # Credit risk examples
│   ├── interest_rates.cpp        # Interest rate derivatives examples
│   └── forex.cpp                 # FX options examples
├── libraries/
│   ├── wab_advanced_quant_fi/    # Core C++ library
│   │   ├── includes/             # Header files
│   │   └── src/                  # Implementation files
│   └── wab_advanced_qf_py/       # Python bindings (pybind11)
│       ├── src/                  # Python binding code
│       └── README.md             # Python-specific documentation
├── tests/                         # Test suite
│   └── test_quantitative_finance.py
├── build/                         # Build artifacts (generated)
├── install/                       # Installation directory (generated)
│   ├── bin/                      # C++ executables
│   ├── lib/                      # C++ libraries
│   └── python/                   # Python module (.so file)
├── requirements.txt               # Python dependencies
└── CMakeLists.txt                # CMake build configuration
```

## Prerequisites

- **C++ Compiler**: C++17 compatible (GCC 7+, Clang 5+, MSVC 2017+)
- **CMake**: Version 3.30 or higher
- **Python**: Version 3.7 or higher (for Python bindings)
- **pybind11**: For Python bindings

## Building the Project

### 1. Clone the Repository

```bash
git clone <repository-url>
cd cpp_advanced_quant_fi
```

### 2. Build with CMake

```bash
mkdir -p build
cd build
cmake ..
make
```

### 3. Install (Optional)

```bash
make install
```

This will install:
- C++ executables to `install/bin/`
- C++ libraries to `install/lib/`
- Python module to `install/python/`

Default installation directory is `<project-root>/install`. You can customize with:
```bash
cmake -DCMAKE_INSTALL_PREFIX=/custom/path ..
```

## Running C++ Applications

After building, run the example applications:

```bash
# From build directory
./bin/equities
./bin/credit_risk
./bin/interest_rates
./bin/forex
```

Or from the install directory:

```bash
# From install directory
./bin/equities
./bin/credit_risk
./bin/interest_rates
./bin/forex
```

## Using the Python Module

### 1. Install Python Dependencies

From the project root:

```bash
pip install -r requirements.txt
```

### 2. Set PYTHONPATH

```bash
export PYTHONPATH=/path/to/install/python:$PYTHONPATH
```

For default installation:
```bash
export PYTHONPATH=$(pwd)/install/python:$PYTHONPATH
```

### 3. Import and Use

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
```

See [libraries/wab_advanced_qf_py/README.md](libraries/wab_advanced_qf_py/README.md) for detailed Python documentation.

## Running Tests

### Python Tests

From the project root:

```bash
# Direct execution
python tests/test_quantitative_finance.py

# With pytest
pytest tests/test_quantitative_finance.py -v

# With coverage
pytest tests/test_quantitative_finance.py -v --cov=wab_advanced_qf_py
```

The test suite automatically detects the installed Python module and validates all functionality.

## Documentation

- **Python Bindings**: See [libraries/wab_advanced_qf_py/README.md](libraries/wab_advanced_qf_py/README.md)
- **API Reference**: Use Python's built-in help:
  ```python
  import wab_advanced_qf_py as qf
  help(qf.EQ1)
  help(qf.CR2)
  ```

## Development

### Adding New Features

1. Add C++ implementation to `libraries/wab_advanced_quant_fi/`
2. Add Python bindings to `libraries/wab_advanced_qf_py/src/pybind_wrapper.cpp`
3. Add tests to `tests/test_quantitative_finance.py`
4. Rebuild and test

### CMake Configuration

The build system uses CMake with the following key features:
- Automatic dependency management
- Python module generation via pybind11
- RPATH configuration for proper library linking
- Separate build and install trees

## License

See [LICENSE.md](LICENSE.md) for details.

## Contributing

This is a personal learning project based on a quantitative finance book. Feel free to fork and experiment!
