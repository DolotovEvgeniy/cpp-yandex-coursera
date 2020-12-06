add_executable(hotel_booking hotel_booking.cpp)
set_target_properties(hotel_booking PROPERTIES
    OUTPUT_NAME "hotel_booking"
    PROJECT_LABEL "hotel_booking"
    RUNTIME_OUTPUT_DIRECTORY "../bin")
