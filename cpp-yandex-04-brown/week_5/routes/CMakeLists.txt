add_executable(routes routes.cpp)
set_target_properties(routes PROPERTIES
    OUTPUT_NAME "routes"
    PROJECT_LABEL "routes"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
