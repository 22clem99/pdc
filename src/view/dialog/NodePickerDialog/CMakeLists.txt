add_library(NodePickerDialog
    NodePickerDialog.cpp
    NodePickerDialog.hpp
)

target_link_libraries(NodePickerDialog
    PUBLIC
        utils
        Node
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)