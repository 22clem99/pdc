add_library(json INTERFACE
    json.hpp
)

target_include_directories(json
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)