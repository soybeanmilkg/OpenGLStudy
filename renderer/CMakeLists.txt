project(renderer)

file(GLOB_RECURSE SOURCE src/**.cpp)

add_library(${PROJECT_NAME}
    ${GLAD_SOURCE}
    ${STB_SOURCE}

    ${SOURCE}
)
