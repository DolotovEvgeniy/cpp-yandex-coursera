set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

SET(CMAKE_CXX_FLAGS  "-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")

add_executable(budget_san budget_san.cpp)
set_target_properties(budget_san PROPERTIES
    OUTPUT_NAME "budget_san"
    PROJECT_LABEL "budget_san"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
