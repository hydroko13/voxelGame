cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



project(voxelGame)



add_executable(voxelGame
${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c # GLAD 



# PROJECT SOURCE CODE
# vvvvvvvvvvvvvvvvvvv

${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/game/game.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/shader/shader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/glerror/glerror.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/shaderProgram/shaderProgram.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/vertexAttribute/vertexAttribute.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/vertexArray/vertexArray.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/vertexBuffer/vertexBuffer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/elementBuffer/elementBuffer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/texture/texture.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/image/image.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/camera/camera.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/camera/camera.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/imageAtlas/imageAtlas.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/util/util.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/blockRegistry/blockRegistry.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/block/block.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/chunk/chunk.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/chunkData/chunkData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/level/level.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/worldgen/worldgen.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/blockSelectorBox/blockSelectorBox.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/dda/dda.cpp

)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw/")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glm/")


target_link_libraries(voxelGame glfw)
target_link_libraries(voxelGame glm)

target_include_directories(voxelGame PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

