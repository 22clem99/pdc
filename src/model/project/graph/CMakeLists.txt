add_library(Graph
    Graph.cpp
    GraphEditor.cpp
)

target_link_libraries(Graph
    PUBLIC
        Node
        Edge
    PRIVATE
        utils
)