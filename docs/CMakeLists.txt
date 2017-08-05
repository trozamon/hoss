add_custom_target(user_doc)
add_custom_command(TARGET user_doc
        COMMAND sphinx-build -b html ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
        )
