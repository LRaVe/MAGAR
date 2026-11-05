# List of project unit tests
add_custom_test(GameState
  TEST_LIBRARIES
    $<TARGET_NAME:project_static>
)
add_custom_test(DrawDice
  TEST_LIBRARIES
    $<TARGET_NAME:project_static>
)
add_custom_test(Pawn
  TEST_LIBRARIES
    $<TARGET_NAME:project_static>
)
add_custom_test(PlayablePawn
  TEST_LIBRARIES
    $<TARGET_NAME:project_static>
)
add_custom_test(Board
  TEST_LIBRARIES
    $<TARGET_NAME:project_static>
)
# vim: set sw=2 sts=2 et:
