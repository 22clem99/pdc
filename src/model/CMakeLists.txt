add_subdirectory(project)

add_library(PDCState
    PDCState.cpp
)

target_link_libraries(PDCState
    PUBLIC
        Project
    PRIVATE
        utils
)