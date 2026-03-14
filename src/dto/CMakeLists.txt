add_library(dto INTERFACE
    NodeData.hpp
)

target_include_directories(dto
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)