cmake_minimum_required(VERSION 3.26)

project(DA_projeto1 LANGUAGES CXX)

add_executable(DA_projeto1
    src/main.cpp
    src/parser/CSVParser.cpp
    src/ui/Menu.cpp
    src/algorithm/FlowNetwork.cpp
    src/algorithm/RiskAnalysis.cpp
    src/output/ReportWriter.cpp
)

target_compile_features(DA_projeto1 PRIVATE cxx_std_17)

target_include_directories(DA_projeto1 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
