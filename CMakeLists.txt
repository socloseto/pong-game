cmake_minimum_required(VERSION 3.15)
project(PongGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
)



set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(sfml)



file(GLOB_RECURSE SOURCES 
    "pong/*.cpp" 
    "pong/*.h" 
    "pong/*.hpp"
)


add_executable(PongGame WIN32 ${SOURCES})


target_compile_definitions(PongGame PRIVATE SFML_STATIC)


target_link_libraries(PongGame PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::Audio 
    SFML::System
    SFML::Main
    opengl32
    winmm
    gdi32
)


set(RES_DIRS audio common texturing ui Objects)
foreach(DIR ${RES_DIRS})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pong/${DIR}")
        add_custom_command(TARGET PongGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
            "${CMAKE_CURRENT_SOURCE_DIR}/pong/${DIR}" 
            "$<TARGET_FILE_DIR:PongGame>/${DIR}"
        )
    endif()
endforeach()