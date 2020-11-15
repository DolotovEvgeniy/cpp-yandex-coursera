SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(synchronized synchronized.cpp)
set_target_properties(synchronized PROPERTIES
    OUTPUT_NAME "synchronized"
    PROJECT_LABEL "synchronized"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
