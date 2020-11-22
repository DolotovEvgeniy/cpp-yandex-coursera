SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(concurrent_map_2 concurrent_map_2.cpp)
set_target_properties(concurrent_map_2 PROPERTIES
    OUTPUT_NAME "concurrent_map_2"
    PROJECT_LABEL "concurrent_map_2"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
