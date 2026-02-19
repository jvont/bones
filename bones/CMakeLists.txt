# file(GLOB_RECURSE bones_SOURCES CONFIGURE_DEPENDS 
#   *.cpp *hpp *h
# )
# add_library(bones ${bones_SOURCES})

set(bones_SOURCES
  # core 
  core/debug/log.cpp
  core/debug/profiler.cpp

  core/events/event_handler.cpp

  core/input/input_handler.cpp

  core/math/color/color_defs.cpp
  core/math/color/color.cpp
  core/math/spatial/point2.cpp
  core/math/spatial/rect.cpp

  core/time/time.cpp
  core/time/update_loop.cpp

  # editor
  editor/editor_imgui_sdl.cpp
  
  # platform
  # platform/gl.cpp
  platform/platform_sdl.cpp
  platform/window_sdl.cpp

  # resources
  resources/image.cpp
  # resources/mesh.cpp
  resources/shader.cpp
  resources/texture.cpp

  # scene
  scene/camera.cpp
  scene/node.cpp
)

add_library(bones ${bones_SOURCES})

target_include_directories(bones 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(bones
  PUBLIC
    glad
    imgui
  PRIVATE
    SDL3::SDL3
    stb_image
)

# fine-grained control of cxx standard
set_target_properties(bones PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

# enable SDL platform backend
target_compile_definitions(bones PRIVATE PLATFORM_SDL)

# add debug definition
target_compile_definitions(bones PRIVATE "$<$<CONFIG:DEBUG>:DEBUG_ENABLED>")
