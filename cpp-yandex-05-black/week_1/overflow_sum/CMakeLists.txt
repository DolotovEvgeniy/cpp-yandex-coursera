add_executable(overflow_sum overflow_sum.cpp)
set_target_properties(overflow_sum PROPERTIES
    OUTPUT_NAME "overflow_sum"
    PROJECT_LABEL "overflow_sum"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
