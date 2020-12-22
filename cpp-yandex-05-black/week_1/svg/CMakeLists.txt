add_executable(svg svg.cpp)
set_target_properties(svg PROPERTIES
    OUTPUT_NAME "svg"
    PROJECT_LABEL "svg"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
