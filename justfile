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

compile-shaders:
    glslc ./shaders/source/shader.vert -o ./shaders/vert.spv
    glslc ./shaders/source/shader.frag -o ./shaders/frag.spv
    glslc ./shaders/source/texture_shader.vert -o ./shaders/texture_vert.spv
    glslc ./shaders/source/texture_shader.frag -o ./shaders/texture_frag.spv
