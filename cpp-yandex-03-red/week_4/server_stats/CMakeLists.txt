add_executable(server_stats stats.cpp server_stats.cpp)
set_target_properties(server_stats PROPERTIES
    OUTPUT_NAME "server_stats"
    PROJECT_LABEL "server_stats"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
