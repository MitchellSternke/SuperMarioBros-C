# Fails if the committed sources in source/SMB differ from what codegen produces.
#
# Usage: cmake -DCODEGEN=<codegen> -DINPUT=<smbdis.asm> -DEXPECTED_DIR=<source/SMB>
#              -DOUTPUT_DIR=<scratch dir> -P CheckGeneratedSources.cmake

file(REMOVE_RECURSE "${OUTPUT_DIR}")
file(MAKE_DIRECTORY "${OUTPUT_DIR}")

execute_process(COMMAND "${CODEGEN}" "${INPUT}" "${OUTPUT_DIR}" RESULT_VARIABLE result)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "codegen failed")
endif()

foreach(file SMB.cpp SMBData.cpp SMBDataPointers.hpp SMBConstants.hpp)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E compare_files "${OUTPUT_DIR}/${file}" "${EXPECTED_DIR}/${file}"
        RESULT_VARIABLE different)
    if(different)
        message(FATAL_ERROR "source/SMB/${file} is out of date: build the 'regenerate' target")
    endif()
endforeach()
