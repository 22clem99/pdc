set(src_files
    test0.cpp
)

foreach(src_file ${src_files})
    get_filename_component(exe_name ${src_file} NAME_WE)

    STRING(CONCAT test_name "view_" ${exe_name})

    add_executable(${test_name}
        ${src_file}
    )

    target_link_libraries(${test_name}
    PUBLIC
        Node
        Graph
        Project
        PDCView
    PRIVATE
        utils
        Qt6::Widgets
        Qt6::Gui
    )

    add_test(NAME ${test_name}
             COMMAND ${test_name})
endforeach()