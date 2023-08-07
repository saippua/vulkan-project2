cmake_minimum_required(VERSION 3.16)

# (TODO) figure out to make a custom toolchain file that has a newer version of clang for cross compile to windows
# set(CMAKE_TOOLCHAIN_FILE "../../Software/glfw/CMake/x86_64-w64-mingw32-clang.cmake")
set(CMAKE_TOOLCHAIN_FILE "./xcompile_toolchain.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(EXECUTABLE_NAME "VulkanStandalone")
set(SHARED_LIBRARY_NAME "VulkanRenderer")


project("VulkanProject" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LD_DEBUG all)

add_compile_options(-Wall)
add_link_options(-static-libstdc++ -static-libgcc)

# Vulkan
set(ENV{VULKAN_SDK} "/mnt/c/VulkanSDK/1.3.243.0/")
find_package(Vulkan REQUIRED)

# GLFW window API for standalone running.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("/home/saippua/Software/glfw" "${CMAKE_SOURCE_DIR}/build/deps/glfw/" SYSTEM)

# OpenGL math library
add_subdirectory("/home/saippua/Software/glm" "${CMAKE_SOURCE_DIR}/build/deps/glm/")


# Targets
# add_executable(${EXECUTABLE_NAME} "./main.cpp")
#
# target_include_directories(${EXECUTABLE_NAME} 
#     PRIVATE "$ENV{VULKAN_SDK}/Include")
#
#   target_link_libraries(${EXECUTABLE_NAME} 
#     PRIVATE ${Vulkan_LIBRARIES}
#     PRIVATE glfw glm pthread)

add_library(${SHARED_LIBRARY_NAME} SHARED "./api.cpp")

target_include_directories(${SHARED_LIBRARY_NAME}
  PRIVATE "$ENV{VULKAN_SDK}/Include")

target_link_libraries(${SHARED_LIBRARY_NAME}
  PRIVATE ${Vulkan_LIBRARIES}
  PRIVATE glm pthread)
