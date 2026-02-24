add_subdirectory(project)

add_library(PDCstate
    PDCState.cpp
)

target_link_libraries(PDCstate
    PUBLIC
        Project
    PRIVATE
        utils
)