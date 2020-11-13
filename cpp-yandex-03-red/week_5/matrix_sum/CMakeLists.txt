SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(matrix_sum matrix_sum.cpp)
set_target_properties(matrix_sum PROPERTIES
    OUTPUT_NAME "matrix_sum"
    PROJECT_LABEL "matrix_sum"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
