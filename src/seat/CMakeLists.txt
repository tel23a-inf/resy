add_library(seat seat.cpp)
target_link_libraries(seat PUBLIC reservation)
target_compile_definitions(seat PUBLIC DOCTEST_CONFIG_DISABLE)

RESY_ADD_INLINE_TESTS(
    SRC_FILE_STEM seat
    TEST_CASES 
      reservations_valid_for_route 
      reservations_overlap_for_route
      seat_valid
      reservations_sorted
      display_for_station
    LIBRARIES reservation_test_lib
)
