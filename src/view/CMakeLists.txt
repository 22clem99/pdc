add_subdirectory(toolbar)

add_library(PDCView
    PDCView.cpp
)

target_include_directories(PDCView
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PDCView
    PUBLIC
        PkgConfig::GGTKMM
)
