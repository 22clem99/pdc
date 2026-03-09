add_library(PDCMenuBar
    PDCMenuBar.cpp
    PDCMenuBar.hpp
)

target_link_libraries(PDCMenuBar
    PUBLIC
        utils
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)