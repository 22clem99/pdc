add_library(ProjectProperties
    ProjectProperties.cpp
    ProjectProperties.hpp
)

target_link_libraries(ProjectProperties
    PUBLIC
        utils
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)