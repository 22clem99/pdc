# add_subdirectory(input)
# add_subdirectory(output)

add_library(Node SHARED
    Node.cpp
    Node.hpp
    NodeNotifier.hpp
    NodeAllocator.cpp
    NodeAllocator.hpp
    ImageInputNode.hpp
    ImageInputNode.cpp
    ImageOutputNode.hpp
    ImageOutputNode.cpp
    ImageRGBSplitterNode.hpp
    ImageRGBSplitterNode.cpp
    ImageRGBCombinerNode.hpp
    ImageRGBCombinerNode.cpp
)

target_link_libraries(Node
    PRIVATE
        utils
        dto
        Qt6::Widgets
        Qt6::Gui
)