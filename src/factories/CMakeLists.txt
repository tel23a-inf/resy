add_library(factories factories.cpp)
target_compile_definitions(factories PUBLIC DOCTEST_CONFIG_DISABLE)

RESY_ADD_INLINE_TESTS(
    SRC_FILE_STEM factories
    TEST_CASES 
      reservation_from_string
      reservations_from_strings
    LIBRARIES reservation_test_lib
)
