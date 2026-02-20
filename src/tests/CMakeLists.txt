
set(src_file
    test0.cpp
)

foreach(src_file ${src_files})

    get_filename_component(exe_name ${src_file} NAME_WE)

    add_executable(${exe_name}
        ${file_list}
    )

    target_link_libraries(${exe_name}
    PRIVATE
        Node
    )
endforeach()



