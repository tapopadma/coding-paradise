include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(
  graph_lib
  graph.cpp
)
add_executable(
  graph_test
  graph_test.cpp
)
target_link_libraries(
  graph_test
  gtest_main
)
target_link_libraries(
  graph_test
  graph_lib
)

include(GoogleTest)
gtest_discover_tests(graph_test)