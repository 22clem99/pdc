cmake_minimum_required(VERSION 3.28)
project(PointDeCroix VERSION 0.0.1 LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

enable_testing()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Find Lib Boost
find_package(Boost REQUIRED COMPONENTS system)

# Find openCV
find_package(OpenCV REQUIRED)


add_subdirectory(src)

add_custom_target(run
    COMMAND LSAN_OPTIONS=suppressions=${CMAKE_SOURCE_DIR}/cmake/lsan.supp
            $<TARGET_FILE:PointDeCroix>
    DEPENDS PointDeCroix
)

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

# Génère version.hpp à partir de version.hpp.in
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/src/version.hpp
    @ONLY
)

# Crée une librairie INTERFACE pour exposer le chemin vers le header généré
add_library(version INTERFACE)
target_include_directories(version INTERFACE
    ${CMAKE_CURRENT_BINARY_DIR}/src/  # <-- c'est ici que le header généré est
)