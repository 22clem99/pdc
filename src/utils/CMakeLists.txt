add_subdirectory(Zip)

add_library(utils
    Log.cpp
    Int.cpp
    Image.cpp
)

target_link_libraries(utils
    PUBLIC
        json
)

target_include_directories(utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)