add_subdirectory(project)

add_library(PDCController
    PDCController.cpp
    PDCController.hpp
)

target_link_libraries(PDCController
    PUBLIC
        ProjectController
        utils
        PDCView

    PRIVATE
        Qt6::Widgets
)