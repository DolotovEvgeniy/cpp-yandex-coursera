SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(course_project_second_part main.cpp parse.cpp search_server.cpp)
set_target_properties(course_project_second_part PROPERTIES
    OUTPUT_NAME "course_project_second_part"
    PROJECT_LABEL "course_project_second_part"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
