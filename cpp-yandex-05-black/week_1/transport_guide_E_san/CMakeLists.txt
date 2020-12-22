set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

SET(CMAKE_CXX_FLAGS  "-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")

add_executable(transport_guide_E_san descriptions.cpp  json.cpp  main.cpp  requests.cpp  sphere.cpp  transport_catalog.cpp  transport_router.cpp  utils.cpp)
set_target_properties(transport_guide_E_san PROPERTIES
    OUTPUT_NAME "transport_guide_E_san"
    PROJECT_LABEL "transport_guide_E_san"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
