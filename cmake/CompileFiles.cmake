function(CompileFiles SOURCE_FILES)
  get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
  message(STATUS "-------------${FOLDER_NAME}")
  foreach(source_file ${SOURCE_FILES})
    get_filename_component(executable_name ${source_file} NAME_WE)
    add_executable(${executable_name} ${source_file})
    set_target_properties(${executable_name} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        # COMPILE_FLAGS "-Wall -fno-elide-constructors"
    )
    target_compile_options(${executable_name} PRIVATE -O3 -Wall -fno-elide-constructors)
    install(TARGETS ${executable_name} DESTINATION "${INSTALL_BIN_DIR}/${FOLDER_NAME}")
  endforeach()
endfunction()
