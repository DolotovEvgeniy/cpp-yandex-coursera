add_executable(ini ini.cpp test_ini.cpp)
set_target_properties(ini PROPERTIES
    OUTPUT_NAME "ini"
    PROJECT_LABEL "ini"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
