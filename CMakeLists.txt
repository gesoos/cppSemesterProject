# cmake_minimum_required(VERSION <specify CMake version here>)
project(Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project main.cpp VCFFile.cpp VCFFile.h VCFRow.cpp VCFRow.h VCFHeader.cpp VCFHeader.h VCFMeta.cpp VCFMeta.h)