add_executable(translator translator.cpp)
set_target_properties(translator PROPERTIES
    OUTPUT_NAME "translator"
    PROJECT_LABEL "translator"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
