# Conference Review Assigner

A C++ application for automated assignment of conference paper reviews using graph algorithms and maximum flow optimization. This tool models the review assignment problem as a flow network to ensure fair and feasible reviewer-paper matching, with support for risk analysis to identify critical reviewer failures.

## Features

- **Interactive Command-Line Interface**: User-friendly menu for configuration and execution
- **Batch Processing Mode**: Process multiple datasets automatically
- **Multiple Matching Modes**: Support for primary and secondary domain matching
- **Risk Analysis**: Identify critical reviewer subsets that could make assignments infeasible
- **CSV Input/Output**: Parse conference datasets and generate assignment reports
- **Doxygen Documentation**: Comprehensive code documentation

## Prerequisites

- C++17 compatible compiler (e.g., GCC, Clang, MSVC)
- CMake 3.26 or higher
- Windows/Linux/macOS

## Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/ConferenceReviewAssigner.git
   cd ConferenceReviewAssigner
   ```

2. Create build directory and compile:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

   Or on Windows with MinGW:
   ```powershell
   mkdir build
   cd build
   cmake -G "MinGW Makefiles" ..
   mingw32-make
   ```

## Usage

### Interactive Mode
Run the application without arguments for the interactive menu:
```bash
./ConferenceReviewAssigner
```

### Batch Mode
Process a dataset directly:
```bash
./ConferenceReviewAssigner -b dataset1.csv output.csv
```

## Input Format

Input files are CSV-formatted with the following sections:

- **#Submissions**: Paper submissions with ID, primary domain, secondary domain
- **#Reviewers**: Reviewers with ID, primary expertise, secondary expertise, max reviews
- **#Parameters**: Configuration like GenerateAssignments mode, RiskAnalysis level
- **#Control**: Additional control parameters

### Matching Modes
- `GenerateAssignments = 1`: Primary submission domain vs primary reviewer expertise
- `GenerateAssignments = 2`: Include secondary submission domain
- `GenerateAssignments = 3`: Include secondary fields on both sides

## Output

The tool generates CSV reports with review assignments and, when enabled, risk analysis results showing critical reviewer combinations.

## Algorithm Overview

The core algorithm uses:
- **Maximum Flow (Edmonds-Karp)**: For feasibility checking and basic assignments
- **Min-Cost Max-Flow**: For optimal assignments considering match quality
- **Combinatorial Risk Analysis**: Enumerates reviewer subsets to identify failure points

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request with detailed description

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

This project was developed as part of a Data Structures and Algorithms course assignment.

## Risk Analysis

- `RiskAnalysis = 0`: disabled
- `RiskAnalysis = 1`: checks whether the failure of a single reviewer makes the assignment infeasible

## Extra Discussion

The theoretical discussion for `RiskAnalysis = K > 1` and the general formulation without risk analysis is available in [Analysis.md](Analysis.md).
