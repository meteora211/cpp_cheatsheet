file(GLOB SOURCE_FILES "*.cc")

CompileFiles("${SOURCE_FILES}")

target_include_directories(class_functor PRIVATE "${CMAKE_SOURCE_DIR}/common")
