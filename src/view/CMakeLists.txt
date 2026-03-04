add_subdirectory(GraphViewer)
add_subdirectory(PDCMenuBar)

add_library(PDCView
    PDCView.cpp
    PDCView.hpp
)

target_link_libraries(PDCView
    PUBLIC
        GraphViewer
        PDCMenuBar
    PRIVATE
        Qt6::Widgets
)