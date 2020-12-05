add_executable(demographic_stats print_stats.cpp)
set_target_properties(demographic_stats PROPERTIES
    OUTPUT_NAME "demographic_stats"
    PROJECT_LABEL "demographic_stats"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
