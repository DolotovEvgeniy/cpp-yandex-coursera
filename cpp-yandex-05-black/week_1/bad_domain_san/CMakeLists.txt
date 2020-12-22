add_executable(bad_domain_san bad_domain_san.cpp)
set_target_properties(bad_domain_san PROPERTIES
    OUTPUT_NAME "bad_domain_san"
    PROJECT_LABEL "bad_domain_san"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
