set(lib_project_target project_static)

set(project_include_dir
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

generate_dia_header(
  "${CMAKE_CURRENT_SOURCE_DIR}/../State.dia"
  "${project_include_dir}"
)

file(GLOB_RECURSE project_sources *.cpp)

if(project_sources)
  add_library(${lib_project_target} STATIC
    ${project_sources}
    ${jsoncpp_sources}
          src/Action.cpp
  )

  add_dependencies(${lib_project_target} generate-headers)

  target_include_directories(${lib_project_target} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${project_include_dir}
    ${jsoncpp_include_dir}
  )

  target_link_libraries(${lib_project_target} PUBLIC
    $<TARGET_NAME:shared_static>
  )
endif()