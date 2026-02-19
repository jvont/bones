# use doctest for testing
FetchContent_Declare(
  doctest
  GIT_REPOSITORY "https://github.com/onqtam/doctest"
  GIT_TAG "v2.4.12"
)
FetchContent_MakeAvailable(doctest)

# file(GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS *.cpp *.h *.hpp)
# add_executable(bones-tests ${TESTS_SOURCES})

# target_link_libraries(bones-tests PRIVATE doctest bones)

# # set compile features
# set_target_properties(bones-tests PROPERTIES
#   CXX_STANDARD 17
#   CXX_STANDARD_REQUIRED ON
#   CXX_EXTENSIONS OFF
# )

# # add doctest tests to CTest
# include(doctest)
# doctest_discover_tests(bones-tests)
