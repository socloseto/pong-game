cmake_minimum_required(VERSION 3.15)

set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(PongGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS Network Graphics Window Audio System Main CONFIG REQUIRED)
file(GLOB_RECURSE SOURCES 
    "*.cpp" 
    "*.h" 
    "*.hpp"
    "*.rc"
)
list(FILTER SOURCES EXCLUDE REGEX ".*/out/.*")
list(FILTER SOURCES EXCLUDE REGEX ".*/build/.*")

add_executable(PongGame WIN32 ${SOURCES})

target_link_libraries(PongGame PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::Audio 
    SFML::System
    SFML::Main
)

target_compile_definitions(PongGame PRIVATE SFML_STATIC)
add_custom_command(TARGET PongGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/pong/audio" "$<TARGET_FILE_DIR:PongGame>/audio"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/pong/common" "$<TARGET_FILE_DIR:PongGame>/common"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/pong/texturing" "$<TARGET_FILE_DIR:PongGame>/texturing"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/pong/ui" "$<TARGET_FILE_DIR:PongGame>/ui"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/pong/Objects" "$<TARGET_FILE_DIR:PongGame>/Objects"
)