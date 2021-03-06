add_library(AliveDllAE SHARED dllmain.cpp)

target_include_directories(AliveDllAE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>)

target_compile_features(AliveDllAE
    PRIVATE cxx_auto_type
    PRIVATE cxx_variadic_templates)

if (MSVC)
    set_target_properties(AliveDllAE PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /functionpadmin:16 /MAP")
    set_target_properties(AliveDllAE PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /functionpadmin:16 /MAP")
endif()

target_compile_definitions(AliveDllAE PRIVATE "_CRT_SECURE_NO_WARNINGS")

target_link_libraries(AliveDllAE AliveLibAE)
if (WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 4)
   target_link_libraries(AliveDllAE Detours)
endif()

if (NOT DEFINED ENV{AE_ROOT})
    message(WARNING "No AE_ROOT environment variable found, resorting to the default path")
    set(AE_PATH "C:\\GOG Games\\Abes Exoddus" )
else()
	file(TO_CMAKE_PATH $ENV{AE_ROOT} AE_PATH)
endif()

# Ninja will die when it sees $(OutDir) as it does not understand what it means, therefore if using msvc only
# use these vars if its msvc and a native vcxproj.
if (MSVC AND CMAKE_GENERATOR MATCHES "Visual Studio")
    add_custom_command(TARGET AliveDllAE
                       POST_BUILD
                       COMMENT "Copying to game dir ${AE_PATH}"
                       COMMAND if not exist "${AE_PATH}" mkdir "${AE_PATH}"
                       COMMAND copy /y "$(OutDir)$(TargetName)$(TargetExt)" "${AE_PATH}\\AliveDllAE.dll"
                       COMMAND copy /y "$(OutDir)$(TargetName).map" "${AE_PATH}\\AliveDllAE.map")
endif()

export(TARGETS AliveDllAE FILE AliveDllAE.cmake)
install(TARGETS AliveDllAE DESTINATION .)

install(FILES "${AE_PATH}\\AliveDllAE.map" DESTINATION ".")

if (MSVC AND CMAKE_GENERATOR MATCHES "Visual Studio")
    if (WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 4)
        add_custom_command(TARGET AliveDllAE POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_INCLUDE_DIR}/../lib/x86/SDL2.dll" "$(OutDir)SDL2.dll")
        INSTALL(FILES "${SDL2_INCLUDE_DIR}/../lib/x86/SDL2.dll" DESTINATION ".")
    else()
        add_custom_command(TARGET AliveDllAE POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_INCLUDE_DIR}/../lib/x64/SDL2.dll" "$(OutDir)SDL2.dll")
        INSTALL(FILES "${SDL2_INCLUDE_DIR}/../lib/x64/SDL2.dll" DESTINATION ".")
    endif()
endif()
