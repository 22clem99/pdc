add_library(GraphViewer
    GraphViewer.cpp
    GraphViewer.hpp
)

target_link_libraries(GraphViewer
    PUBLIC
        utils
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)