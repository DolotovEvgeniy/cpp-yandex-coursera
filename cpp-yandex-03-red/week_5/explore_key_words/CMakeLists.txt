SET(CMAKE_CXX_FLAGS  "-pthread")
add_executable(explore_key_words explore_key_words.cpp)
set_target_properties(explore_key_words PROPERTIES
    OUTPUT_NAME "explore_key_words"
    PROJECT_LABEL "explore_key_words"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
