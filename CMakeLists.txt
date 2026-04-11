cmake_minimum_required(VERSION 3.26)

project(ConferenceReviewAssigner LANGUAGES CXX)

add_executable(ConferenceReviewAssigner
    src/main.cpp
    src/parser/CSVParser.cpp
    src/ui/Menu.cpp
    src/algorithm/FlowNetwork.cpp
    src/algorithm/RiskAnalysis.cpp
    src/output/ReportWriter.cpp
)

target_compile_features(ConferenceReviewAssigner PRIVATE cxx_std_17)

target_include_directories(ConferenceReviewAssigner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
