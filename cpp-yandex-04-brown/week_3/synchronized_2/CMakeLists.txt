SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(synchronized_2 synchronized_2.cpp)
set_target_properties(synchronized_2 PROPERTIES
    OUTPUT_NAME "synchronized_2"
    PROJECT_LABEL "synchronized_2"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
