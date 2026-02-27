# add_subdirectory(input)
# add_subdirectory(output)

add_library(Node SHARED
    Node.cpp
    NodeAllocator.cpp
    ImageInputNode.cpp
)

target_link_libraries(Node
    # PUBLIC
    #     Input
    #     Output
    PRIVATE
        utils
)