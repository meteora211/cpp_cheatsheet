add_executable(initialization initialization.cc)
set_target_properties(initialization PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_compile_options(initialization PRIVATE -fno-elide-constructors)
install(TARGETS initialization DESTINATION "${INSTALL_BIN_DIR}/initialization")
