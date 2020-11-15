SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(concurrent_map concurrent_map.cpp)
set_target_properties(concurrent_map PROPERTIES
    OUTPUT_NAME "concurrent_map"
    PROJECT_LABEL "concurrent_map"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
