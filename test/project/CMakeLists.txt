# List of project unit tests
add_custom_test(GameState
  TEST_LIBRARIES
    $<TARGET_NAME:project_static>
)

# vim: set sw=2 sts=2 et:
