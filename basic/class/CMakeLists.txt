file(GLOB SOURCE_FILES "*.cc")

set(USE_CXX11 0)
if (${USE_CXX11})
  set(CMAKE_CXX_STANDARD 11)
endif()
CompileFiles("${SOURCE_FILES}")
if (${USE_CXX11})
  target_compile_options(constructor PRIVATE -O3)
  # NOTE: use cxx11 without following options will cause constructor compile fails.
  # See details in mandatory copy elision
  target_compile_definitions(constructor PRIVATE CTOR=1)
endif()

