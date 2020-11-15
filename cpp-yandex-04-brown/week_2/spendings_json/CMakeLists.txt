add_executable(spendings_json spendings_json.cpp json.cpp)
set_target_properties(spendings_json PROPERTIES
    OUTPUT_NAME "spendings_json"
    PROJECT_LABEL "spendings_json"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
