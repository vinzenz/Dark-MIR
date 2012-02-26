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
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "optimize" }


	project "server"
		kind "consoleapp"
		language "c"
		files { "../src/server/*.c", "../src/common/*.c", "../include/*.h" }
		
		buildoptions { "--std=c99 -Wall -pedantic `sdl-config --cflags` -I../include -DSERVER" }
		linkoptions { "`sdl-config --libs`" }
		links { "SDL_net", "SDL_image", "SDL_ttf", "m", "SDL_gfx" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "optimize" }


	project "servernew"
		kind "consoleapp"
		language "c"
		files { "../src/servernew/*.cc" }
		
		buildoptions { "--std=c++0x -Wall -pedantic `sdl-config --cflags` -I../include -pthread" }
		linkoptions { "`sdl-config --libs`" }
		links { "boost_system", "boost_thread", "boost_program_options" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "optimize" }
