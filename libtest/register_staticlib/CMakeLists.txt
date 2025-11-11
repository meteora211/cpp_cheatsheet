set(CMAKE_CXX_STANDARD 17)

# NOTE: If build example togather with register. The print works
# add_executable(register_example
#   register_example.cc
#   register.cc
#   derived_entry_a.cc
# )

# NOTE: If build example and link with static library. The register doesn't work
file(GLOB SOURCE_FILES "*.cc")
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/register_example.cc")
add_library(register_staticlib STATIC ${SOURCE_FILES})

# Build the example executable and link it to the static library
add_executable(register_example register_example.cc)
target_link_libraries(register_example PRIVATE register_staticlib)

# NOTE: force-load the static library so static initializers run
# target_link_options(register_example PRIVATE "-Wl,-force_load,$<TARGET_FILE:register_staticlib>")
