cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



project(voxelGame)

add_executable(voxelGame
${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c # GLAD 


# PROJECT SOURCE CODE
# vvvvvvvvvvvvvvvvvvv

${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glm/")


target_link_libraries(voxelGame glfw)
target_link_libraries(voxelGame glm)

target_include_directories(voxelGame PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

