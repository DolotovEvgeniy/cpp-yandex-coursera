add_executable(spendings_xml spendings_xml.cpp xml.cpp)
set_target_properties(spendings_xml PROPERTIES
    OUTPUT_NAME "spendings_xml"
    PROJECT_LABEL "spendings_xml"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
