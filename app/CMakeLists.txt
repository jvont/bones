add_executable(app main.cpp)

target_link_libraries(app PRIVATE bones)

# set compile features
set_target_properties(app PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

# copy resource files to executable target directory
file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS 
  ${CMAKE_CURRENT_SOURCE_DIR}/resources/*
)
target_configure_files(app ${RESOURCE_FILES})