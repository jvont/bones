# file(GLOB_RECURSE bones_SOURCES CONFIGURE_DEPENDS 
#   *.cpp *hpp *h
# )
# add_library(bones ${bones_SOURCES})

set(bones_SOURCES
  bones/backend/backend_sdl.cpp
)

add_library(bones ${bones_SOURCES})

target_include_directories(bones PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(bones
  PUBLIC
    imgui
  PRIVATE
    SDL3::SDL3
    SDL3_shadercross::SDL3_shadercross
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
