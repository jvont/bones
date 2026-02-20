# include SDL
add_subdirectory(SDL)

# configure SDL_shadercross build
set(SDLSHADERCROSS_DXC ON CACHE BOOL "Enable HLSL compilation via DXC" FORCE)
set(SDLSHADERCROSS_VENDORED ON CACHE BOOL "Use local dependencies" FORCE)
set(SDL3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL CACHE STRING "SDL3 Directory" FORCE)
add_subdirectory(SDL_shadercross)

# include local stb_image library
add_subdirectory(stb_image)

# create imgui cmake library
add_library(imgui STATIC
  imgui/backends/imgui_impl_sdl3.cpp
  imgui/backends/imgui_impl_sdlgpu3.cpp

  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp

  imgui/imgui.cpp
)

target_include_directories(imgui PUBLIC imgui)
target_link_libraries(imgui PRIVATE SDL3::SDL3)
