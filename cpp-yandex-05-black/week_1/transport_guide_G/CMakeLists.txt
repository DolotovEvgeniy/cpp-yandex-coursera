add_executable(transport_guide_G descriptions.cpp main.cpp requests.cpp sphere_projection.cpp transport_catalog.cpp utils.cpp json.cpp map_renderer.cpp sphere.cpp svg.cpp transport_router.cpp)
set_target_properties(transport_guide_G PROPERTIES
    OUTPUT_NAME "transport_guide_G"
    PROJECT_LABEL "transport_guide_G"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
