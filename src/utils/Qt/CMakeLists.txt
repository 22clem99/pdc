add_library(QtUtils
    ImageUtils.cpp
)

target_link_libraries(QtUtils
    PRIVATE
        utils
    PUBLIC
        Qt6::Widgets
        Qt6::Gui
        ${OpenCV_LIBS}
)

target_include_directories(QtUtils
    SYSTEM PUBLIC
        ${OpenCV_INCLUDE_DIRS}
)