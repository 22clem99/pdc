add_subdirectory(node)
add_subdirectory(edge)
add_subdirectory(graph)

add_library(Project
    Project.cpp
)

target_link_libraries(Project
    PUBLIC
        ZipUtils
        Graph
        version
    PRIVATE
        utils
        json
        Qt6::Widgets
        Qt6::Gui
)