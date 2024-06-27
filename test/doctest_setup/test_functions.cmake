
# Hilfsfunktion zum erstellen von Test-Targets und zugehörigen Tests.
# Erwartet zwei Parameter:
# 1. Der Dateiname der Testquelle ohne Endung.
# 2. Eine Liste von Testfällen, die als Argumente an das Testprogramm übergeben werden sollen.
#    In der Quelldatei müssen diese Testfälle mittels `TEST_CASE(<name>) { ... }` definiert sein.
function(RESY_ADD_INLINE_TESTS)
    set(options)
    set(one_value_args SRC_FILE_STEM)
    set(multi_value_args TEST_CASES LIBRARIES)
    cmake_parse_arguments("resy_cmake" "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    set (SOURCE_NAME ${resy_cmake_SRC_FILE_STEM})
    set (TEST_TARGET ${SOURCE_NAME}_test)
    set (TEST_LIB ${SOURCE_NAME}_test_lib)
    set (TEST_SOURCE ${resy_cmake_SRC_FILE_STEM}.cpp)
    set (TEST_CASES ${resy_cmake_TEST_CASES})
    set (LINK_LIBRARIES ${resy_cmake_LIBRARIES})

    add_library(${TEST_LIB} ${TEST_SOURCE})
    target_link_libraries(${TEST_LIB} PUBLIC doctest_main)
    add_executable(${TEST_TARGET} ${TEST_SOURCE})
    target_link_libraries(${TEST_TARGET} PUBLIC ${TEST_LIB})
    
    foreach(TEST_CASE ${TEST_CASES})
        add_test(NAME ${SOURCE_NAME}::${TEST_CASE} COMMAND ${TEST_TARGET} --test-case=${TEST_CASE})
        message(STATUS "Added test ${SOURCE_NAME}::${TEST_CASE}")
        message(STATUS "Command: ${TEST_TARGET} --test-case=${TEST_CASE}")
    endforeach()

    foreach(LIBRARY ${LINK_LIBRARIES})
        target_link_libraries(${TEST_TARGET} PUBLIC ${LIBRARY})
    endforeach()
    
endfunction(RESY_ADD_INLINE_TESTS)
