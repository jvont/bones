# add stb_image library
add_subdirectory(stb_image)

# fetch SDL3 library
FetchContent_Declare(
  SDL
	GIT_REPOSITORY "git@github.com:libsdl-org/SDL.git"
  GIT_TAG "release-3.4.0"
)
FetchContent_MakeAvailable(SDL)

# fetch imgui/create cmake library
FetchContent_Declare(
  imgui
	GIT_REPOSITORY "git@github.com:ocornut/imgui.git"
  GIT_TAG "v1.92.6"
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlgpu3.cpp

  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp

  ${imgui_SOURCE_DIR}/imgui.cpp
)

target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
target_link_libraries(imgui PRIVATE SDL3::SDL3)
