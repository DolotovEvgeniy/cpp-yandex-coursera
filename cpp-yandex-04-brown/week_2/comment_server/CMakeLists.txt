add_executable(comment_server comment_server.cpp)
set_target_properties(comment_server PROPERTIES
    OUTPUT_NAME "comment_server"
    PROJECT_LABEL "comment_server"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
