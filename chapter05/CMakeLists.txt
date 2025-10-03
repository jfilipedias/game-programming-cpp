cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(chapter05)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

find_package(OpenGL REQUIRED)

add_subdirectory(../vendor/SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL EXCLUDE_FROM_ALL)
add_subdirectory(../vendor/SDL_image ${CMAKE_CURRENT_BINARY_DIR}/SDL_image EXCLUDE_FROM_ALL)

file(GLOB SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        ../vendor/glad/src/gl.c)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ../vendor/glad/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3_image::SDL3_image
        SDL3::SDL3
        OpenGL::GL)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3_image::SDL3_image>
            $<TARGET_FILE:SDL3::SDL3>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif ()
