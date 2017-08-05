set(CORE_TESTS
        MessageTest
        )

add_definitions(-DBOOST_TEST_DYN_LINK)

foreach(test ${CORE_TESTS})
        get_source_file_property(DEFINES ${test}.cpp COMPILE_DEFINITIONS)
        set_source_files_properties(${test}.cpp
                PROPERTIES
                COMPILE_DEFINITIONS "${DEFINES};BOOST_TEST_MODULE=${test}"
                )

        add_executable(${test} ${test}.cpp)
        target_link_libraries(${test}
                hoss-core
                ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                )

        add_test(NAME ${test}
                COMMAND ${test}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                )
endforeach()
