project(sp02)

file(GLOB_RECURSE SOURCE src/**.cpp)

add_executable(${PROJECT_NAME}
    ${GLAD_SOURCE}

    ${SOURCE}
)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS})
