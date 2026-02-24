add_subdirectory(input)
add_subdirectory(output)

add_library(Node
    Node.cpp
)

target_link_libraries(Node
    PRIVATE
        utils
)