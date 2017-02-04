cmake_minimum_required(VERSION 3.5)
project(nfa)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.cpp nfa_parser.cpp nfa_parser.h textutils.cpp nfa.cpp nfa.h)
add_executable(nfa ${SOURCE_FILES})