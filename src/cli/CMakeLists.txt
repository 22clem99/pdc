add_library(CMDLineParser
    PDCCMDLineParser.hpp
    PDCCMDLineParser.cpp
)

target_include_directories(CMDLineParser
    PRIVATE
        Qt6::Widgets
        Qt6::Gui
        Qt6::Core
)