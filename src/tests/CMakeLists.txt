set(src_files
    test0.cpp
    test1.cpp
    test2.cpp
    test3.cpp
)

foreach(src_file ${src_files})
    get_filename_component(exe_name ${src_file} NAME_WE)

    add_executable(${exe_name}
        ${src_file}
    )

    target_link_libraries(${exe_name}
    PUBLIC
        Node
        Graph
        Project
    PRIVATE
        utils
    )

    add_test(NAME ${exe_name}
             COMMAND ${exe_name})
endforeach()
