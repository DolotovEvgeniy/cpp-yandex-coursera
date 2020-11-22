add_executable(pipeline pipeline.cpp)
set_target_properties(pipeline PROPERTIES
    OUTPUT_NAME "pipeline"
    PROJECT_LABEL "pipeline"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
