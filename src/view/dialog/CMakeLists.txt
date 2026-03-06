add_subdirectory(NewProjectDialog)

add_library(dialog
)

target_link_libraries(dialog
    PUBLIC
        NewProjectDialog
        utils
    PRIVATE
        Qt6::Widgets
)