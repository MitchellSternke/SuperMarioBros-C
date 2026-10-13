# Translates the 6502 disassembly (docs/smbdis.asm) into the C++ sources in source/SMB.
# Requires Bison and Flex, which the top-level CMakeLists.txt checks for.

BISON_TARGET(parser asm6502.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)
FLEX_TARGET(scanner asm6502.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)

add_executable(codegen
    ${BISON_parser_OUTPUTS}
    ${FLEX_scanner_OUTPUTS}
    ast.cpp
    main.cpp
    translator.cpp)
target_include_directories(codegen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
