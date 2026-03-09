add_subdirectory(GraphViewer)
add_subdirectory(PDCMenuBar)
add_subdirectory(dialog)

add_library(PDCView
    PDCView.cpp
    PDCView.hpp
    ImageView.hpp
)

target_link_libraries(PDCView
    PUBLIC
        utils
        GraphViewer
        PDCMenuBar
        dialog
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::Core
)