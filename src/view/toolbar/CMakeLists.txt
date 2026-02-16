add_library(Toolbar
    Toolbar.cpp
)

target_include_directories(Toolbar
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Toolbar
    PUBLIC
        PkgConfig::GGTKMM
)
