add_library(GraphViewer
    GraphViewer.cpp
    GraphViewer.hpp
)

target_link_libraries(GraphViewer
    PRIVATE
        Qt6::Widgets
)