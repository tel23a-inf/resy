add_executable(resy resy.cpp)
target_compile_definitions(resy PUBLIC DOCTEST_CONFIG_DISABLE)
target_link_libraries(resy files factories reservation seat)

set(RESY_BIN_DIR ${PROJECT_SOURCE_DIR}/resy-bin)
set(TESTDATA_DIR ${PROJECT_SOURCE_DIR}/testdata)

add_custom_target(copy_resy_and_testdata ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RESY_BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:resy> ${RESY_BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${TESTDATA_DIR} ${RESY_BIN_DIR}
    DEPENDS resy
)

add_custom_target(run_resy
    COMMAND resy
    DEPENDS copy_resy_and_testdata
    WORKING_DIRECTORY ${RESY_BIN_DIR}
)
