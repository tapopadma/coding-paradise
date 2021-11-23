include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(
  cayley_lib
  cayley.cpp
)
add_executable(
  cayley_test
  cayley_test.cpp
)
target_link_libraries(
  cayley_test
  gtest_main
)
target_link_libraries(
  cayley_test
  cayley_lib
)

add_library(
  modulo_lib
  modulo.cpp
)
add_executable(
  modulo_test
  modulo_test.cpp
)
target_link_libraries(
  modulo_test
  gtest_main
)
target_link_libraries(
  modulo_test
  modulo_lib
)

include(GoogleTest)
gtest_discover_tests(cayley_test)
gtest_discover_tests(modulo_test)