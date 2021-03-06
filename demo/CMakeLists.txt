project(demo)
cmake_minimum_required(VERSION 2.8)
file(GLOB_RECURSE SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

# Windows API UNICODE variable
add_definitions(-DUNICODE)

add_executable(${PROJECT_NAME} ${SRC_LIST})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ceppengine ${CMAKE_CURRENT_BINARY_DIR}/ceppengine)

target_link_libraries(${PROJECT_NAME}
    ceppengine
    user32
    gdi32
    ${OPENAL_TARGET}
    freetype
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/libEGL.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/libGLESv2.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/assimp.lib
)

include_directories(src
    ${CMAKE_CURRENT_SOURCE_DIR}/../ceppengine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/openalsoft/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/freetype/include
)
