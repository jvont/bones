# modified from: https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html
# initialize, fetch and checkout any nested git submodules
function(configure_submodules)
  find_package(Git QUIET)
  if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(STATUS "Checking git submodules")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      RESULT_VARIABLE GIT_SUBMOD_RESULT
    )
    if(GIT_SUBMOD_RESULT)
      message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}. Please checkout submodules.")
    endif()
  endif()
endfunction()