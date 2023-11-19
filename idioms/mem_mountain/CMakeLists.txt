file(GLOB SOURCE_FILES "*.cc")

CompileFiles(${SOURCE_FILES})

target_include_directories(basic_pipeline PRIVATE "${CMAKE_SOURCE_DIR}/common")
