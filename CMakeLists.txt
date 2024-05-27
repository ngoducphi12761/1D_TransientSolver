cmake_minimum_required(VERSION 3.5)

project(applicationTask LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(applicationTask main.cpp
    fvm.cpp
    incompressible.cpp
    incompressible.h
    appincompsoftinway.cpp
    incompSoftInWay.cpp
    incompSoftInWay.h
    compressible.cpp
    compressible.h
    createTime.h
    initializationvalues.h
    initializationvalues.cpp
)

install(TARGETS applicationTask
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
