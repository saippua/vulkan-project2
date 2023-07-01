cmake_minimum_required(VERSION 3.16)

project("VulkanProject" LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(LD_DEBUG all)

add_compile_options(-Wall)
add_link_options(-static-libstdc++ -static-libgcc)

# Vulkan
set(VULKAN_SDK "/mnt/c/VulkanSDK/1.3.243.0/")
set(Vulkan_LIBRARY "${VULKAN_SDK}/Lib/")
set(Vulkan_INCLUDE_DIR "${VULKAN_SDK}/Include/")
find_package(Vulkan REQUIRED)
include_directories("${Vulkan_INCLUDE_DIR}")
link_libraries("/mnt/c/Windows/System32/vulkan-1.dll") # For cross compiling on WSL

add_executable(${PROJECT_NAME} "./main.cpp")
# OpenGL math library
# add_subdirectory("./deps/glm")

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("/home/saippua/Projects/VulkanProject/deps/glfw" "${CMAKE_SOURCE_DIR}/build/deps/glfw/" SYSTEM)
# target_link_libraries(${PROJECT_NAME} glfw)

# GLM
add_subdirectory("/home/saippua/Projects/VulkanProject/deps/glm" "${CMAKE_SOURCE_DIR}/build/deps/glm/")



# add_subdirectory("./src/vulkanRenderer")
# add_subdirectory("./src/application")

target_link_libraries(${PROJECT_NAME} 
    # PUBLIC SimpleWindow 
    # PUBLIC renderer
    PUBLIC glfw glm)

