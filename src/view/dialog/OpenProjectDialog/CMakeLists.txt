add_library(OpenProjectDialog
    OpenProjectDialog.cpp
    OpenProjectDialog.hpp
)

target_link_libraries(OpenProjectDialog
    PUBLIC
        utils
    PRIVATE
        Qt6::Widgets
)