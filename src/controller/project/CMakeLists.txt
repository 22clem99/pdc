add_subdirectory(cmds)

add_library(ProjectController
    ProjectController.cpp
    ProjectController.hpp
    GraphController.cpp
    GraphController.hpp
    GenericPDCController.hpp
)

target_link_libraries(ProjectController
    PUBLIC
        CMDs
        utils
        PDCView
        dto
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)