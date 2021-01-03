add_executable(json_printer json_printer.cpp)
set_target_properties(json_printer PROPERTIES
    OUTPUT_NAME "json_printer"
    PROJECT_LABEL "json_printer"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
