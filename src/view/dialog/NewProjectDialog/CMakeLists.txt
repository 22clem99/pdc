add_library(NewProjectDialog
    NewProjectDialog.cpp
    NewProjectDialog.hpp
)

target_link_libraries(NewProjectDialog
    PUBLIC
        utils
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)