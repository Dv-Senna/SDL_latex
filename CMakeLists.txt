set(CMAKE_PROJECT_MINIMUM_VERSION 3.20)
cmake_minimum_required(VERSION 3.20)

project(template
	VERSION 2.0.0
	LANGUAGES C
)

set(PROJECT_ACRONYM TEX)
string(TOUPPER ${PROJECT_ACRONYM} PROJECT_ACRONYM_UPPERCASE)
set(PROJECT_C_DIALECT 23)

option(BUILD_TESTS "BUILD_TESTS" OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT DEFINED TEX_HANDLED_VENDORS)
	add_subdirectory(vendors/SDL)
	add_subdirectory(vendors/SDL_image)
	if (WIN32)
		function(CLONE_SDL_DLL target)
			add_custom_command(
				TARGET ${target} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different
				$<TARGET_FILE:SDL3::SDL3>
				$<TARGET_FILE_DIR:${target}>
			)
		endfunction()
		function(CLONE_SDL_IMAGE_DLL target)
			add_custom_command(
				TARGET ${target} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different
				$<TARGET_FILE:SDL3_image::SDL3_image>
				$<TARGET_FILE_DIR:${target}>
			)
		endfunction()
	endif()
endif()


set(DEPS_INCLUDE_DIRS
	SDL3::Headers
	SDL3_image::Headers
)
set(DEPS_LIBRARIES
	SDL3::SDL3
	SDL3_image::SDL3_image
)

add_subdirectory(lib)
add_subdirectory(sandbox)
if (BUILD_TESTS)
	add_subdirectory(tests)
endif()
