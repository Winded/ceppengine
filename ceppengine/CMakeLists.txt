project(ceppengine)
cmake_minimum_required(VERSION 2.8)
file(GLOB_RECURSE SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Windows API UNICODE variable
add_definitions(-DUNICODE)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/portaudio ${CMAKE_CURRENT_BINARY_DIR}/portaudio)

target_link_libraries(${PROJECT_NAME} 
    user32
    gdi32
    portaudio
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/libEGL.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/libGLESv2.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/assimp.lib)

include_directories(src
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/portaudio/include)

add_custom_command(TARGET ceppengine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_BINARY_DIR}/../thirdparty/lib/"
        ${CMAKE_BINARY_DIR})

add_custom_command(TARGET ceppengine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:portaudio>
        ${CMAKE_BINARY_DIR})
