# DA_projeto1

Conference review assignment tool based on graph modeling and max-flow.

## Features

- Interactive command-line menu
- Batch execution mode
- Parsing of project datasets
- Review assignment generation
- Detection of missing reviews in infeasible instances
- Risk analysis for `RiskAnalysis = 1`
- Doxygen documentation

## Build

From the project folder:

```powershell
& "C:\msys64\ucrt64\bin\g++.exe" -std=c++17 -I src src/main.cpp src/parser/CSVParser.cpp src/ui/Menu.cpp src/algorithm/FlowNetwork.cpp src/algorithm/RiskAnalysis.cpp src/output/ReportWriter.cpp -o build\DA_projeto1.exe
```

## Run

Interactive mode:

```powershell
.\build\DA_projeto1.exe
```

Batch mode:

```powershell
.\build\DA_projeto1.exe -b inputs\dataset1.csv output.csv
```

## Input Structure

The input files are divided into the following sections:

- `#Submissions`
- `#Reviewers`
- `#Parameters`
- `#Control`

## Matching Modes

- `GenerateAssignments = 1`: primary submission domain vs primary reviewer expertise
- `GenerateAssignments = 2`: broader compatibility including submission secondary domain
- `GenerateAssignments = 3`: broader compatibility including secondary fields on both sides

## Risk Analysis

- `RiskAnalysis = 0`: disabled
- `RiskAnalysis = 1`: checks whether the failure of a single reviewer makes the assignment infeasible

## Extra Discussion

The theoretical discussion for `RiskAnalysis = K > 1` and the general formulation without risk analysis is available in [Analysis.md](Analysis.md).
