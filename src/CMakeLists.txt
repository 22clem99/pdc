add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(controller)
add_subdirectory(utils)

add_subdirectory(tests)

add_executable(PointDeCroix
    main.cpp
)

target_link_libraries(PointDeCroix
  PRIVATE
    PDCView
)