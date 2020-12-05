add_executable(expression_tree main.cpp Common.cpp)
set_target_properties(expression_tree PROPERTIES
    OUTPUT_NAME "expression_tree"
    PROJECT_LABEL "expression_tree"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
