add_executable(unique_ptr unique_ptr.cpp)
set_target_properties(unique_ptr PROPERTIES
    OUTPUT_NAME "unique_ptr"
    PROJECT_LABEL "unique_ptr"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
