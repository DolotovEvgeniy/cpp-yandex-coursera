add_executable(bad_domains bad_domains.cpp)
set_target_properties(bad_domains PROPERTIES
    OUTPUT_NAME "bad_domains"
    PROJECT_LABEL "bad_domains"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
