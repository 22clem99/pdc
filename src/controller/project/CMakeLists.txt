add_subdirectory(cmds)

add_library(ProjectController
    ProjectController.cpp
    ProjectController.hpp
    GenericPDCController.hpp
)

target_link_libraries(ProjectController
    PUBLIC
        CMDs
        utils
        PDCView
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)