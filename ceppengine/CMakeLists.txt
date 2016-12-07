project(ceppengine)
cmake_minimum_required(VERSION 2.8)
file(GLOB_RECURSE SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Windows API UNICODE variable
add_definitions(-DUNICODE)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/openalsoft ${CMAKE_CURRENT_BINARY_DIR}/openalsoft)
if(WIN32)
    set(OPENAL_TARGET OpenAL32)
else()
    set(OPENAL_TARGET openal)
endif()

target_link_libraries(${PROJECT_NAME} 
    user32
    gdi32
    ${OPENAL_TARGET}
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/libEGL.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/libGLESv2.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lib/assimp.lib
)

include_directories(src
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/openalsoft/include
)

add_custom_command(TARGET ceppengine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_BINARY_DIR}/../thirdparty/lib/"
        ${CMAKE_BINARY_DIR})

add_custom_command(TARGET ceppengine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${OPENAL_TARGET}>
        ${CMAKE_BINARY_DIR})
