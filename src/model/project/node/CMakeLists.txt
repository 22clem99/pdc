# add_subdirectory(node_library)

add_library(Node SHARED
    Node.cpp
    Node.hpp
    NodeNotifier.hpp
    NodeAllocator.cpp
    NodeAllocator.hpp
    node_library/input/ImageInputNode.hpp
    node_library/input/ImageInputNode.cpp
    node_library/output/ImageOutputNode.hpp
    node_library/output/ImageOutputNode.cpp
    node_library/rgb_workflow/ImageRGBSplitterNode.hpp
    node_library/rgb_workflow/ImageRGBSplitterNode.cpp
    node_library/rgb_workflow/ImageRGBCombinerNode.hpp
    node_library/rgb_workflow/ImageRGBCombinerNode.cpp
)

target_link_libraries(Node
    PRIVATE
        utils
        dto
        Qt6::Widgets
        Qt6::Gui
)