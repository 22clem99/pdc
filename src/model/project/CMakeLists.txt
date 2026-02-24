add_subdirectory(node)

add_library(Project
    Project.cpp
)

target_link_libraries(Project
    PUBLIC
        Log
        Node
    PRIVATE
        utils
)