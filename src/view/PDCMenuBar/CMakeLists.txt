add_library(PDCMenuBar
    PDCMenuBar.cpp
    PDCMenuBar.hpp
)

target_link_libraries(PDCMenuBar
    PRIVATE
        Qt6::Widgets
)