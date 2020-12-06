add_executable(demographic_stats_tests print_stats.cpp)
set_target_properties(demographic_stats_tests PROPERTIES
    OUTPUT_NAME "demographic_stats_tests"
    PROJECT_LABEL "demographic_stats_tests"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
