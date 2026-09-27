cmake_minimum_required(VERSION 3.16)

project(5G-Handover-Failure-Analyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(handover_analyzer
    backend/src/main.cpp
    backend/src/DataReader.cpp
    backend/src/FailureAnalyzer.cpp
    backend/src/HandoverAnalyzer.cpp
    backend/src/CellHandoverStats.cpp
)

target_include_directories(handover_analyzer
    PRIVATE
    backend/include
)
