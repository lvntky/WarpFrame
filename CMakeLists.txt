cmake_minimum_required(VERSION 3.25)
project(warpframe LANGUAGES CXX)

# ------------------------------- Options ------------------------------------
option(WARPFRAME_FIXED_POINT "Enable fixed-point math path" ON)
option(WARPFRAME_AFFINE_TEX  "Use affine texture mapping (PS1 style)" ON)
option(WARPFRAME_DITHER      "Enable 15-bit dither output" ON)
option(WARPFRAME_MT          "Enable multithreaded tiling" ON)
option(WARPFRAME_BUILD_TESTS "Build unit tests" ON)
option(WARPFRAME_BUILD_BENCH "Build microbenchmarks" ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ------------------------------- CPM ----------------------------------------
# Expect: cmake/CPM.cmake present (bootstrap file)
set(CPM_DOWNLOAD_VERSION 0.40.2)
set(CPM_USE_LOCAL_PACKAGES ON)
include(cmake/CPM.cmake)

# --------------------------- Dependencies -----------------------------------
# fmt
CPMAddPackage("gh:fmtlib/fmt#11.0.2")

# SDL2 (build static by default)
CPMAddPackage(
    NAME SDL2
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG release-2.30.9
    OPTIONS "SDL_SHARED OFF" "SDL_STATIC ON"
)

# Detect an SDL2 CMake target we can link against
set(SDL2_LIB_TARGET "")
set(SDL2_MAIN_TARGET "")
if (TARGET SDL2::SDL2-static)
    set(SDL2_LIB_TARGET SDL2::SDL2-static)
    if (TARGET SDL2::SDL2main)
        set(SDL2_MAIN_TARGET SDL2::SDL2main)
    endif()
elseif (TARGET SDL2-static)
    set(SDL2_LIB_TARGET SDL2-static)
elseif (TARGET SDL2::SDL2)
    set(SDL2_LIB_TARGET SDL2::SDL2)
    if (TARGET SDL2::SDL2main)
        set(SDL2_MAIN_TARGET SDL2::SDL2main)
    endif()
else()
    message(FATAL_ERROR "Could not find an SDL2 target (SDL2::SDL2-static, SDL2-static, or SDL2::SDL2).")
endif()

# stb (header-only)
CPMAddPackage(NAME stb GITHUB_REPOSITORY nothings/stb GIT_TAG master)

# tinyobjloader
CPMAddPackage("gh:tinyobjloader/tinyobjloader#v2.0.0rc13")

# Dear ImGui
CPMAddPackage(
    NAME imgui
    GITHUB_REPOSITORY ocornut/imgui
    GIT_TAG v1.91.0
)

# Build ImGui with SDL2 + SDL_Renderer2 backend (no OpenGL)
add_library(imgui_sdl STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)
target_include_directories(imgui_sdl PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_sdl PUBLIC ${SDL2_LIB_TARGET})
if (WIN32 AND SDL2_MAIN_TARGET)
    # Some SDL builds provide SDL2main; link it and avoid SDL redef of main
    target_link_libraries(imgui_sdl PUBLIC ${SDL2_MAIN_TARGET})
    target_compile_definitions(imgui_sdl PUBLIC SDL_MAIN_HANDLED)
endif()

# ------------------------------- Sources ------------------------------------
file(GLOB_RECURSE WARPFRAME_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(warpframe ${WARPFRAME_SOURCES})

target_include_directories(warpframe PUBLIC
    include
    ${stb_SOURCE_DIR}
)

# Build-time feature flags
if(WARPFRAME_FIXED_POINT)
    target_compile_definitions(warpframe PRIVATE WARPFRAME_FIXED_POINT=1)
endif()
if(WARPFRAME_AFFINE_TEX)
    target_compile_definitions(warpframe PRIVATE WARPFRAME_AFFINE_TEX=1)
endif()
if(WARPFRAME_DITHER)
    target_compile_definitions(warpframe PRIVATE WARPFRAME_DITHER=1)
endif()
if(WARPFRAME_MT)
    target_compile_definitions(warpframe PRIVATE WARPFRAME_MT=1)
endif()

# Link libs for the app
target_link_libraries(warpframe PRIVATE
    ${SDL2_LIB_TARGET}
    imgui_sdl
    fmt::fmt
    tinyobjloader
)

# Windows: ensure SDL doesn't override our main if backend didn't define it already
if (WIN32)
    target_compile_definitions(warpframe PRIVATE SDL_MAIN_HANDLED)
endif()

# ------------------------------- Tests --------------------------------------
if(WARPFRAME_BUILD_TESTS)
    enable_testing()
    CPMAddPackage("gh:google/googletest#v1.15.2")
    add_executable(warpframe_tests tests/test_sanity.cpp)
    target_link_libraries(warpframe_tests GTest::gtest_main)
    add_test(NAME sanity COMMAND warpframe_tests)
endif()

# ------------------------------ Benchmarks ----------------------------------
if(WARPFRAME_BUILD_BENCH)
    CPMAddPackage("gh:martinus/nanobench#v4.3.11")
    add_executable(warpframe_bench bench/bench_fill.cpp)
    target_link_libraries(warpframe_bench PRIVATE nanobench fmt::fmt)
endif()

# ------------------------------ Notes ---------------------------------------
# If your distro prefers system SDL2 instead of CPM:
#   find_package(SDL2 REQUIRED)
#   set(SDL2_LIB_TARGET SDL2::SDL2)  # or SDL2::SDL2-static on some setups
# and remove the CPM SDL2 block above.
