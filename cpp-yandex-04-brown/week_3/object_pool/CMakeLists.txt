add_executable(object_pool object_pool.cpp)
set_target_properties(object_pool PROPERTIES
    OUTPUT_NAME "object_pool"
    PROJECT_LABEL "object_pool"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
