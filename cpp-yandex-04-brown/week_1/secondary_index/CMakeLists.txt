add_executable(secondary_index secondary_index.cpp)
set_target_properties(secondary_index PROPERTIES
    OUTPUT_NAME "secondary_index"
    PROJECT_LABEL "secondary_index"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
