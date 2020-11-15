SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(course_project_first_part main.cpp parse.cpp search_server.cpp)
set_target_properties(synchronized PROPERTIES
    OUTPUT_NAME "course_project_first_part"
    PROJECT_LABEL "course_project_first_part"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
