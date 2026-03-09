add_library(CMDs
    ProjectCMD.cpp
)

target_link_libraries(CMDs
    PUBLIC
        utils
        PDCView
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)