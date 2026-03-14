add_library(Graph
    Graph.hpp
    Graph.cpp
    GraphEditor.hpp
    GraphEditor.cpp
)

target_link_libraries(Graph
    PUBLIC
        Node
        Edge
    PRIVATE
        utils
        dto
        Qt6::Widgets
        Qt6::Gui
)