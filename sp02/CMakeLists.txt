project(sp02)

file(GLOB_RECURSE CODE_HEADER src/**.h)
file(GLOB_RECURSE CODE_SOURCE src/**.cpp)

add_executable(${PROJECT_NAME}
    ${GLAD_SOURCE}

    ${CODE_HEADER}
    ${CODE_SOURCE}
)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS})
