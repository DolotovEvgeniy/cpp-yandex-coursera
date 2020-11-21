add_executable(game_object collide.cpp geo2d.cpp)
set_target_properties(game_object PROPERTIES
    OUTPUT_NAME "game_object"
    PROJECT_LABEL "game_object"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
