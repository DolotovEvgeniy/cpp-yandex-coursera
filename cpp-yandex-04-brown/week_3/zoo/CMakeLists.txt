add_executable(zoo zoo.cpp)
set_target_properties(zoo PROPERTIES
    OUTPUT_NAME "zoo"
    PROJECT_LABEL "zoo"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
