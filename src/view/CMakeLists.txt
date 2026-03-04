add_subdirectory(GraphViewer)

add_library(PDCView
    PDCView.cpp
    PDCView.hpp
)

target_link_libraries(PDCView
    PUBLIC
        GraphViewer
    PRIVATE
        Qt6::Widgets
)