cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ar VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake")

find_program(CMAKE cmake)
if(NOT CMAKE)
    message(FATAL_ERROR "CMake binary not found!")
endif()

add_custom_target(
    UpdateConfigHeader
    COMMAND "${CMAKE}" -D BUILD_NUMBER=${BUILD_NUMBER} -P ${CMAKE_CURRENT_SOURCE_DIR}/options.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  string(REPLACE "/W3" "" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "${CMAKE_BINARY_DIR}/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

enable_testing()

add_subdirectory(3rdParty)
add_subdirectory(Source/AliveLibCommon)
add_subdirectory(Source/AliveLibAO)
add_subdirectory(Source/AliveLibAE)
add_subdirectory(Source/AliveExe)
add_subdirectory(assets)

if (WIN32)
    add_subdirectory(Source/AliveDllAE)
    add_subdirectory(Source/AliveDllAO)
endif()

add_dependencies(AliveLibCommon UpdateConfigHeader)

if(WIN32)
    # On Windows generate ZIP packages
    SET(CPACK_GENERATOR "ZIP")
endif()
INCLUDE(CPack)
