# pull in dependencies
add_subdirectory(glad)
add_subdirectory(SDL)
add_subdirectory(stb_image)

# create CMake library for imgui
add_library(imgui STATIC
  imgui/backends/imgui_impl_opengl3.cpp
  imgui/backends/imgui_impl_sdl.cpp

  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp

  imgui/imgui.cpp
)

target_include_directories(imgui
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui>
)

target_link_libraries(imgui
  glad
  SDL2main
  SDL2-static
)