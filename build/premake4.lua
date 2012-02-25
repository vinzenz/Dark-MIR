-- Premake build script
solution "dark-mir"
	configurations { "Debug", "Release" }

	project "mir"
		kind "consoleapp"
		language "c"
		files { "../src/client/*.c", "../src/common/*.c", "../include/*.h" }
		
		buildoptions { "--std=c99 -Wall -pedantic `sdl-config --cflags` -I../include -DCLIENT" }
		linkoptions { "`sdl-config --libs`" }
		links { "SDL_net", "SDL_image", "SDL_ttf", "m", "SDL_gfx" }
		
		configuration "debug"
			defines { "debug" }
			flags { "symbols" }

		configuration "release"
			defines { "ndebug" }
			flags { "optimize" }


	project "server"
		kind "consoleapp"
		language "c"
		files { "../src/console/*.c", "../src/common/*.c", "../include/*.h" }
		
		buildoptions { "--std=c99 -Wall -pedantic `sdl-config --cflags` -I../include -DSERVER" }
		linkoptions { "`sdl-config --libs`" }
		links { "SDL_net", "SDL_image", "SDL_ttf", "m", "SDL_gfx" }
		
		configuration "debug"
			defines { "debug" }
			flags { "symbols" }

		configuration "release"
			defines { "ndebug" }
			flags { "optimize" }
