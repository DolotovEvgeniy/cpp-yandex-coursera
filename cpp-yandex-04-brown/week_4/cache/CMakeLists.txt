SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(cache main.cpp Solution.cpp)
set_target_properties(cache PROPERTIES
    OUTPUT_NAME "cache"
    PROJECT_LABEL "cache"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
