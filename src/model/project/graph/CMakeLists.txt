add_library(Graph SHARED
    Graph.cpp
)

target_link_libraries(Graph
    PUBLIC
        Node
        Edge
    PRIVATE
        utils
)