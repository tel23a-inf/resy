
# Hilfsfunktion zum erstellen von Test-Targets und zugehörigen Tests.
# Erwartet zwei Parameter:
# 1. Der Dateiname der Testquelle ohne Endung.
# 2. Eine Liste von Testfällen, die als Argumente an das Testprogramm übergeben werden sollen.
#    In der Quelldatei müssen diese Testfälle mittels `TEST_CASE(<name>) { ... }` definiert sein.
function(RESY_ADD_INLINE_TESTS)
    set(options)
    set(one_value_args SRC_FILE_STEM)
    set(multi_value_args TEST_CASES)
    cmake_parse_arguments("resy_cmake" "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    set (SOURCE_NAME ${resy_cmake_SRC_FILE_STEM})
    set (TEST_TARGET ${SOURCE_NAME}_test)
    set (TEST_SOURCE ${resy_cmake_SRC_FILE_STEM}.cpp)
    set (TEST_CASES ${resy_cmake_TEST_CASES})

    add_executable(${TEST_TARGET} ${TEST_SOURCE})
    target_link_libraries(${TEST_TARGET} doctest_main)
    
    foreach(TEST_CASE ${TEST_CASES})
        add_test(NAME ${SOURCE_NAME}::${TEST_CASE} COMMAND ${TEST_TARGET} --test-case=${TEST_CASE})
    endforeach()
    
endfunction(RESY_ADD_INLINE_TESTS)
