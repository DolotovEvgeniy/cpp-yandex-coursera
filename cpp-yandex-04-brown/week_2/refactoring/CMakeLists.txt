add_executable(refactoring refactoring.cpp json.cpp xml.cpp)
set_target_properties(refactoring PROPERTIES
    OUTPUT_NAME "refactoring"
    PROJECT_LABEL "refactoring"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
