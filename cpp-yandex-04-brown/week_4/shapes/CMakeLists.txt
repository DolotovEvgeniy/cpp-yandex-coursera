add_executable(shapes main.cpp Textures.cpp Solution.cpp)
set_target_properties(shapes PROPERTIES
    OUTPUT_NAME "shapes"
    PROJECT_LABEL "shapes"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
