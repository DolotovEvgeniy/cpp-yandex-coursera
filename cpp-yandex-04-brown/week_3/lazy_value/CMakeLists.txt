add_executable(lazy_value lazy_value.cpp)
set_target_properties(lazy_value PROPERTIES
    OUTPUT_NAME "lazy_value"
    PROJECT_LABEL "lazy_value"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
