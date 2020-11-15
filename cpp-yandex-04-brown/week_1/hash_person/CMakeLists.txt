add_executable(hash_person hash_person.cpp)
set_target_properties(hash_person PROPERTIES
    OUTPUT_NAME "hash_person"
    PROJECT_LABEL "hash_person"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
