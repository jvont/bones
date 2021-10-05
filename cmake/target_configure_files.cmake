# copy files to a target's post-build output directory
# output location of files is relative to the caller directory
# 
# example usage:
#   add_executable(main PRIVATE lib1 lib2)
#   target_configure_files(main 
#                          ${CMAKE_CURRENT_SOURCE_DIR}/imageA.png 
#                          ${CMAKE_CURRENT_SOURCE_DIR}/subdir/imageB.png)
# post-build output:
#   imageA.png -> '[path-to-main.exe]/imageA.png'
#   imageB.png -> '[path-to-main.exe]/subdir/imageB.png'

macro(target_configure_files NAME)
  foreach(filepath ${ARGN})
    # TODO: error handling (check if path exists and is file)
    file(RELATIVE_PATH filepath_rel ${CMAKE_CURRENT_SOURCE_DIR} ${filepath})
    get_filename_component(filename ${filepath} NAME)

    add_custom_command(TARGET app POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        "${filepath}"
        "$<TARGET_FILE_DIR:${NAME}>/${filepath_rel}"
    )
  endforeach()
endmacro()
