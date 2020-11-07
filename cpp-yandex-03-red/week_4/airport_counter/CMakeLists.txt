add_executable(airport_counter airport_counter.cpp)
set_target_properties(airport_counter PROPERTIES
    OUTPUT_NAME "airport_counter"
    PROJECT_LABEL "airport_counter"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
