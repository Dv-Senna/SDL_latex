workspace "SDL_latex"
	configurations {"debug", "release"}


project "lib"
	kind "StaticLib"
	language "C"
	targetdir "lib/bin"
	objdir "lib/obj"
	targetname "SDL2_latex"
	warnings "Extra"

	files {
		"lib/src/**.c",
		"lib/include/**.h"
	}

	includedirs {
		"lib/include/SDL2",
		"vendors/SDL2/include",
		"vendors/SDL2/include/SDL2",
		"vendors/SDL2_image/include",
	}

	filter "configurations:debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:release"
		defines {"NDEBUG"}
		optimize "On"


project "Sandbox"
	kind "ConsoleApp"
	language "C"
	targetdir "sandbox/bin"
	objdir "sandbox/obj"
	targetname "sandbox"
	warnings "Extra"

	files {
		"sandbox/src/**.c"
	}

	includedirs {
		"sandbox/include",
		"lib/include",
		"vendors/SDL2/include",
		"vendors/SDL2/include/SDL2",
		"vendors/SDL2_image/include",
	}

	libdirs {
		"lib/bin",
		"vendors/SDL2/lib",
		"vendors/SDL2_image/lib",
	}

	links {
		"SDL2_latex",
		"SDL2_image",
		"SDL2",
		"SDL2main"
	}


	filter {"system:Windows", "toolset:gcc"}
		links "mingw32"

	filter "configurations:debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:release"
		defines {"NDEBUG"}
		optimize "On"




