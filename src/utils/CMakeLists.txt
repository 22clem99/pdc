add_subdirectory(Zip)
add_subdirectory(Qt)

add_library(utils
    Log.cpp
    Int.cpp
    Image.cpp
)

target_link_libraries(utils
    PUBLIC
        json
        QtUtils
    PRIVATE
        ${OpenCV_LIBS}
)

target_include_directories(utils
    SYSTEM PUBLIC
        ${OpenCV_INCLUDE_DIRS}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)