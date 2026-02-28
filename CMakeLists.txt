cmake_minimum_required(VERSION 3.28)
project(PointDeCroix LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


enable_testing()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Find dependencies
# find GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GGTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

# find Lib Boost
find_package(Boost REQUIRED COMPONENTS system)

add_subdirectory(src)

# Cherche cppcheck
find_program(CPPCHECK_EXECUTABLE cppcheck)
if(CPPCHECK_EXECUTABLE)
    # --- Target pour générer le rapport XML ---
    add_custom_target( cppcheck-run
        COMMAND ${CPPCHECK_EXECUTABLE}
                --project=${CMAKE_BINARY_DIR}/compile_commands.json
                --enable=all
                --inconclusive
                --std=c++23
                --force
                --xml
                --xml-version=2
                --error-exitcode=1
                --suppress=missingIncludeSystem
                --suppress=*:*/build/*
                --suppress=*:*/external/*
                2> ${CMAKE_BINARY_DIR}/cppcheck-report.xml
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running cppcheck and generating XML report"
        DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
    )

    # --- Test CTest qui échoue si cppcheck détecte des erreurs ---
    add_test(NAME cppcheck-test
        COMMAND ${CPPCHECK_EXECUTABLE}
                --project=${CMAKE_BINARY_DIR}/compile_commands.json
                --enable=all
                --inconclusive
                --std=c++23
                --force
                --error-exitcode=1
                --suppress=missingIncludeSystem
                --suppress=*:*/build/*
                --suppress=*:*/external/*
    )
else()
    message(WARNING "cppcheck not found: cppcheck-run and cppcheck-test will be skipped")
endif()