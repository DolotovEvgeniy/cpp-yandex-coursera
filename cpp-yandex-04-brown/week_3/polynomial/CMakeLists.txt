add_executable(polynomial polynomial.cpp)
set_target_properties(polynomial PROPERTIES
    OUTPUT_NAME "polynomial"
    PROJECT_LABEL "polynomial"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
