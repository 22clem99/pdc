set(src_files
    test0.cpp
    test1.cpp
    test2.cpp
    test3.cpp
    test4.cpp
    test_graph_valid_no_head.cpp
    test_graph_valid_no_tail.cpp
    test_graph_valid_not_connected.cpp
)

foreach(src_file ${src_files})
    get_filename_component(exe_name ${src_file} NAME_WE)

    STRING(CONCAT test_name "model_" ${exe_name})

    add_executable(${test_name}
        ${src_file}
    )

    target_link_libraries(${test_name}
    PUBLIC
        Node
        Graph
        Project
    PRIVATE
        utils
        Qt6::Widgets
        Qt6::Gui
    )

    add_test(NAME ${test_name}
             COMMAND ${test_name})
endforeach()
