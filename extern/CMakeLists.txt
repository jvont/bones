# fetch and link external libraries

# SDL
FetchContent_Declare(
  SDL
	GIT_REPOSITORY "git@github.com:libsdl-org/SDL.git"
  GIT_TAG "release-3.4.0"
)
FetchContent_MakeAvailable(SDL)

# glad
FetchContent_Declare(
  glad
	GIT_REPOSITORY "git@github.com:Dav1dde/glad.git"
  GIT_TAG "v2.0.8"
)
FetchContent_MakeAvailable(glad)

# ImGui
FetchContent_Declare(
  imgui
	GIT_REPOSITORY "git@github.com:ocornut/imgui.git"
  GIT_TAG "v1.92.6"
)
FetchContent_MakeAvailable(imgui)

# create CMake library for imgui
add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp

  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp

  ${imgui_SOURCE_DIR}/imgui.cpp
)

target_include_directories(imgui
  PUBLIC
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
)

target_link_libraries(imgui
  glad
  SDL3::SDL3
)