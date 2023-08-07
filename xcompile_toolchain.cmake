
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(BIN_DIR "/home/saippua/Software/llvm-mingw-20230614-ucrt-ubuntu-20.04-x86_64/bin")
set(CMAKE_SYSTEM_NAME       Windows)
set(CMAKE_SYSTEM_VERSION    1)
set(CMAKE_C_COMPILER        "${BIN_DIR}/x86_64-w64-mingw32-clang")
set(CMAKE_CXX_COMPILER      "${BIN_DIR}/x86_64-w64-mingw32-clang++")
set(CMAKE_RC_COMPILER       "${BIN_DIR}/x86_64-w64-mingw32-llvm-windres")
set(CMAKE_RANLIB            "${BIN_DIR}/x86_64-w64-mingw32-llvm-ranlib")

set(CMAKE_CXX_COMPILER_TARGET "x86_64-pc-windows-gnu")
set(CMAKE_C_COMPILER_TARGET "x86_64-pc-windows-gnu")

# set(CMAKE_FIND_ROOT_PATH "")
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
