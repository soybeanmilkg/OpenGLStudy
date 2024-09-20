project(sp01)

file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources
    DESTINATION ${OUTPUT_PATH}
    FILES_MATCHING PATTERN *
)

file(GLOB_RECURSE CODE_HEADER src/**.h)
file(GLOB_RECURSE CODE_SOURCE src/**.cpp)

add_executable(${PROJECT_NAME}
    ${GLAD_SOURCE}
    ${IMGUI_SOURCE}
    ${STB_SOURCE}

    ${CODE_HEADER}
    ${CODE_SOURCE}
)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS})
