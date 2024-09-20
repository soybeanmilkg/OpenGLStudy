project(renderer)

file(GLOB_RECURSE CODE_HEADER src/**.h)
file(GLOB_RECURSE CODE_SOURCE src/**.cpp)

add_library(${PROJECT_NAME}
    ${GLAD_SOURCE}
    ${STB_SOURCE}

    ${CODE_HEADER}
    ${CODE_SOURCE}
)
