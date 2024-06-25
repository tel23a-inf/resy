add_library(reservation reservation.cpp)
target_compile_definitions(reservation PUBLIC DOCTEST_CONFIG_DISABLE)

RESY_ADD_INLINE_TESTS(
    SRC_FILE_STEM reservation
    TEST_CASES
      origin_pos
      destination_pos
      is_valid_for_route
)
