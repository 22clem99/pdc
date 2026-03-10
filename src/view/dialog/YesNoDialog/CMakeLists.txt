add_library(YesNoDialog
    YesNoDialog.hpp
)

target_link_libraries(YesNoDialog
    PUBLIC
        utils
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)