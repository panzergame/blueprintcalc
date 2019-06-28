cmake_minimum_required(VERSION 3.0)

project(blueprintcalc)

add_executable(blueprintcalc main.cpp)

install(TARGETS blueprintcalc RUNTIME DESTINATION bin)
