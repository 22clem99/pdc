add_subdirectory(NewProjectDialog)
add_subdirectory(OpenProjectDialog)

add_library(dialog
)

target_link_libraries(dialog
    PUBLIC
        OpenProjectDialog
        NewProjectDialog
        utils
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)