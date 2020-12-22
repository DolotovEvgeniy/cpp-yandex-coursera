set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_executable(bad_domain_san bad_domain_san.cpp)
set_target_properties(bad_domain_san PROPERTIES
    OUTPUT_NAME "bad_domain_san"
    PROJECT_LABEL "bad_domain_san"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
