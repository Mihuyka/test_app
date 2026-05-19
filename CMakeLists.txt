cmake_minimum_required(VERSION 3.20)

project(test_gtk VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

add_executable(test_app
    src/main.cpp
    src/bodies.cpp
    include/header.hpp
)

set_property(TARGET test_app PROPERTY CXX_STANDARD 20)
set_property(TARGET test_app PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(test_app PRIVATE include)

target_link_libraries(test_app PRIVATE PkgConfig::GTKMM)