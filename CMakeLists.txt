cmake_minimum_required(VERSION 3.16)

project(smbc
    DESCRIPTION "Super Mario Bros. translated to C++"
    LANGUAGES CXX)

option(SMBC_BUILD_TESTS "Build the regression tests" ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(SMBC_WARNINGS /W3)
else()
    set(SMBC_WARNINGS -Wall -Wextra -Wpedantic)
endif()

#---------------------------------------------------------------------
# Game engine: the translated game code and NES emulation (no SDL)
#---------------------------------------------------------------------

add_library(smb_core STATIC
    source/Emulation/APU.cpp
    source/Emulation/Controller.cpp
    source/Emulation/Palette.cpp
    source/Emulation/PPU.cpp
    source/SMB/SMB.cpp
    source/SMB/SMBData.cpp
    source/SMB/SMBEngine.cpp)
target_include_directories(smb_core PUBLIC source)
target_compile_options(smb_core PRIVATE ${SMBC_WARNINGS})

# The translated code jumps between labels, many of which are never targeted
set_source_files_properties(source/SMB/SMB.cpp source/SMB/SMBData.cpp PROPERTIES
    COMPILE_OPTIONS "$<IF:$<CXX_COMPILER_ID:MSVC>,/bigobj,-Wno-unused-label>")

#---------------------------------------------------------------------
# Game executable
#---------------------------------------------------------------------

find_package(SDL2 REQUIRED)
if(NOT TARGET SDL2::SDL2)
    # Older SDL2 packages only provide variables
    add_library(SDL2::SDL2 INTERFACE IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${SDL2_LIBRARIES}")
endif()

add_executable(smbc
    source/Configuration.cpp
    source/Frontend/AudioOutput.cpp
    source/Frontend/Display.cpp
    source/Frontend/Input.cpp
    source/Main.cpp)
target_link_libraries(smbc PRIVATE smb_core SDL2::SDL2)
if(TARGET SDL2::SDL2main)
    target_link_libraries(smbc PRIVATE SDL2::SDL2main)
endif()
target_compile_options(smbc PRIVATE ${SMBC_WARNINGS})

install(TARGETS smbc RUNTIME DESTINATION bin)

#---------------------------------------------------------------------
# Code generator (optional: only needed to regenerate source/SMB)
#---------------------------------------------------------------------

find_package(BISON 3.0)
find_package(FLEX)
if(BISON_FOUND AND FLEX_FOUND)
    add_subdirectory(codegen)

    add_custom_target(regenerate
        COMMAND codegen ${PROJECT_SOURCE_DIR}/docs/smbdis.asm ${PROJECT_SOURCE_DIR}/source/SMB
        COMMENT "Regenerating source/SMB from docs/smbdis.asm"
        VERBATIM)
else()
    message(STATUS "Bison 3+ and Flex not found: the codegen and 'regenerate' targets are unavailable")
endif()

#---------------------------------------------------------------------
# Tests
#---------------------------------------------------------------------

if(SMBC_BUILD_TESTS)
    enable_testing()

    add_executable(smbc_regression tests/RegressionTest.cpp)
    target_link_libraries(smbc_regression PRIVATE smb_core)
    target_compile_options(smbc_regression PRIVATE ${SMBC_WARNINGS})
    add_test(NAME regression COMMAND smbc_regression)

    if(TARGET codegen)
        add_test(NAME generated_sources_up_to_date
            COMMAND ${CMAKE_COMMAND}
                -DCODEGEN=$<TARGET_FILE:codegen>
                -DINPUT=${PROJECT_SOURCE_DIR}/docs/smbdis.asm
                -DEXPECTED_DIR=${PROJECT_SOURCE_DIR}/source/SMB
                -DOUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/generated-check
                -P ${PROJECT_SOURCE_DIR}/tests/CheckGeneratedSources.cmake)
    endif()
endif()
