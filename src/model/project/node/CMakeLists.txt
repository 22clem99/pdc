# add_subdirectory(input)
# add_subdirectory(output)

add_library(Node SHARED
    PortAllocator.cpp
    Node.cpp
    NodeAllocator.cpp
    ImageInputNode.cpp
    ImageOutputNode.cpp
    ImageRGBSplitterNode.cpp
    ImageRGBCombinerNode.cpp
)

target_link_libraries(Node
    # PUBLIC
    #     Input
    #     Output
    PRIVATE
        utils
)