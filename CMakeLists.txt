cmake_minimum_required(VERSION 3.16)
project(GraphViz)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(GraphViz
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/IOUtils.cpp
  ${PROJECT_SOURCE_DIR}/src/SimpleGraph.cpp
)

target_link_libraries(GraphViz PRIVATE Qt6::Core Qt6::Widgets)

target_include_directories(GraphViz PRIVATE ${PROJECT_SOURCE_DIR}/src/)

function(copy_resources_to_target_dir target)
  add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "$<TARGET_PROPERTY:${target},SOURCE_DIR>/res"
            "$<TARGET_PROPERTY:${target},BINARY_DIR>/res"
    )
endfunction()

copy_resources_to_target_dir(GraphViz)
