add_library(CMDs
    GraphCMD.hpp
    ProjectCMD.hpp
)

target_link_libraries(CMDs
    PUBLIC
        utils
        PDCView
        dto
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
)