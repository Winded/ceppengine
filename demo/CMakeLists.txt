project(demo)
cmake_minimum_required(VERSION 2.8)
file(GLOB_RECURSE SRC_LIST "src/*")

# Windows API UNICODE variable
add_definitions(-DUNICODE)

add_executable(${PROJECT_NAME} ${SRC_LIST})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ceppengine ${CMAKE_CURRENT_BINARY_DIR}/ceppengine)

target_link_libraries(${PROJECT_NAME} ceppengine user32 gdi32)

include_directories(src ../include ../ceppengine/src)

#add_custom_command(TARGET demo POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "$<TARGET_FILE_DIR:demo>/lua/lua.dll"
#        $<TARGET_FILE_DIR:demo>)
