add_executable(booking test.cpp)
set_target_properties(booking PROPERTIES
    OUTPUT_NAME "booking"
    PROJECT_LABEL "booking"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
