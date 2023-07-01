toolchain := "../../Software/glfw/CMake/x86_64-w64-mingw32.cmake"

alias b := build
alias r := run

build:
    mkdir -p build
    cd build && \
    cmake -D CMAKE_TOOLCHAIN_FILE={{toolchain}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. && \
    make

run:
    ./build/VulkanProject.exe

br:
    just build
    just run

# compile-shaders:
#     glslc ./resources/shaders/source/shader.vert -o ./resources/shaders/vert.spv
#     glslc ./resources/shaders/source/shader.frag -o ./resources/shaders/frag.spv
#     glslc ./resources/shaders/source/texture_shader.vert -o ./resources/shaders/texture_vert.spv
#     glslc ./resources/shaders/source/texture_shader.frag -o ./resources/shaders/texture_frag.spv
