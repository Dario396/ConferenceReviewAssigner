cmake_minimum_required(VERSION 3.26)
project(DA_projeto1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DA_projeto1
        src/main.cpp
        src/parser/CSVParser.cpp
)
