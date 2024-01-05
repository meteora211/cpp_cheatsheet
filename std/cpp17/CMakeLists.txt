file(GLOB SOURCE_FILES "*.cc")

set(CMAKE_CXX_STANDARD 17)
CompileFiles("${SOURCE_FILES}")

# set_target_properties(mandatory_copy_elision PROPERTIES
#     CXX_STANDARD 17
#     CXX_STANDARD_REQUIRED YES
#     CXX_EXTENSIONS NO
# )
