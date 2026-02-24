cmake_minimum_required(VERSION 3.28)

set (CMAKE_CXX_STANDARD 20)

project(PointDeCroix)

## Find dependencies
# find GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GGTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

# find Lib Boost
find_package(Boost REQUIRED COMPONENTS system)

add_subdirectory(src)