add_library(utils
    Log.cpp
    Int.cpp
)

target_include_directories(utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# add_library(Int
#     Int.cpp
# )

# add_library(Log
#     Log.cpp
# )
