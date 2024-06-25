add_library(factories factories.cpp)
target_compile_definitions(factories PUBLIC DOCTEST_CONFIG_DISABLE)

RESY_ADD_INLINE_TESTS(
    SRC_FILE_STEM factories
    TEST_CASES 
      seats_from_reservations
      reservation_from_string
      reservations_from_strings
    LIBRARIES reservation
)
