if (BUILD_TESTING)
    set(TEST_NAME "LibraryTests")

    add_executable(${TEST_NAME}
        "Placeholder.cpp"
    )

    target_compile_features(${TEST_NAME} PRIVATE cxx_std_20)
    target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main ${DYNAMIC_LIBRARY})
    target_include_directories(${TEST_NAME} PRIVATE ${LIBRARY_INCLUDE_PATH})

    add_test(NAME ${TEST_NAME}
        COMMAND ${TEST_NAME}
    )

    gtest_discover_tests(${TEST_NAME})
endif()