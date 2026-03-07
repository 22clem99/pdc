add_library(ZipUtils
    ZipReader.cpp
    ZipWriter.cpp
)

target_link_libraries(ZipUtils
    PUBLIC
        miniz
)