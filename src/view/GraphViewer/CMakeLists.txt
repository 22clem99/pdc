add_library(GraphViewer
    GraphViewer.cpp
    GraphViewer.hpp
    GraphScene.cpp
    GraphScene.hpp
    NodeView.hpp
    PortView.hpp
)

target_link_libraries(GraphViewer
    PUBLIC
        utils
        dto
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)