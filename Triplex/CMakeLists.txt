cmake_minimum_required(VERSION 3.10)
project(Triplex)

set(CMAKE_CXX_STANDARD 11)

add_executable(Triplex main.cpp bindRNA/BindRNA.cpp bindRNA/BindRNA.h Triplexator/Triplexator.cpp Triplexator/Triplexator.h structRNASites.h)