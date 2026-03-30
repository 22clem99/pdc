add_subdirectory(NewProjectDialog)
add_subdirectory(OpenProjectDialog)
add_subdirectory(NodePickerDialog)
add_subdirectory(ProjectProperties)

add_library(dialog
)

target_link_libraries(dialog
    PUBLIC
        OpenProjectDialog
        NewProjectDialog
        NodePickerDialog
        ProjectProperties
        utils
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)