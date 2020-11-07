add_executable(split_into_sentences split_into_sentences.cpp)
set_target_properties(split_into_sentences PROPERTIES
    OUTPUT_NAME "split_into_sentences"
    PROJECT_LABEL "split_into_sentences"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
