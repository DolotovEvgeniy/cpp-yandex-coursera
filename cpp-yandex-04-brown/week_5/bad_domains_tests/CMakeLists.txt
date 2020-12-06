add_executable(bad_domains_test test_domains.cpp)
set_target_properties(bad_domains_test PROPERTIES
    OUTPUT_NAME "bad_domains_test"
    PROJECT_LABEL "bad_domains_test"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
