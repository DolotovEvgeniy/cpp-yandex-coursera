add_executable(stats_aggregator main.cpp stats_aggregator.cpp stats_aggregator_test.cpp)
set_target_properties(stats_aggregator PROPERTIES
    OUTPUT_NAME "stats_aggregator"
    PROJECT_LABEL "stats_aggregator"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
