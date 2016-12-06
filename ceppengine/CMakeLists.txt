project(ceppengine)
cmake_minimum_required(VERSION 2.8)
file(GLOB_RECURSE SRC_LIST "src/*")

# Windows API UNICODE variable
add_definitions(-DUNICODE)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} 
    user32
    gdi32
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libEGL.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libGLESv2.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/assimp.lib)

include_directories(src/ceppengine ../include)

add_custom_command(TARGET ceppengine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_BINARY_DIR}/../lib/"
        ${CMAKE_BINARY_DIR})
