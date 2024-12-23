cmake_minimum_required(VERSION 3.4.1)

add_library(
		restoration
		SHARED
		Main.cpp
		ImGui/imgui.cpp
		ImGui/imgui_impl_android.cpp
		ImGui/imgui_impl_opengl3.cpp
		ImGui/imgui_tables.cpp
		ImGui/imgui_widgets.cpp
		ImGui/imgui_demo.cpp
		ImGui/imgui_draw.cpp
		KittyMemory/KittyMemory.cpp
		KittyMemory/KittyScanner.cpp
		KittyMemory/MemoryPatch.cpp
		KittyMemory/MemoryBackup.cpp
		KittyMemory/KittyUtils.cpp
		xdl/xdl.c
		xdl/xdl_util.c
		xdl/xdl_lzma.c
		xdl/xdl_linker.c
		xdl/xdl_iterate.c
	# imgui/imgui.cpp
	# imgui/imgui_widgets.cpp
	# imgui/imgui_tables.cpp
	# imgui/imgui_draw.cpp
	# imgui/imgui_demo.cpp
	# imgui/imgui_impl_android.cpp
	# imgui/imgui_impl_opengl3.cpp
)

find_library(log-lib log)
find_library(egl EGL)
find_library(android android)
find_library(GLESV2_LIB GLESv2)
find_library(LZ_LIB z)
# find_package(curl REQUIRED CONFIG)
if (${ANDROID_PLATFORM_LEVEL} LESS 12)
	message(FATAL_ERROR "OpenGL 2 is not supported before API level 11 /
					  (currently using ${ANDROID_PLATFORM_LEVEL}).")
	return()
elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
	add_definitions("-DDYNAMIC_ES3")
	set(GL3STUB_SRC gl3stub.c)
	set(OPENGL_LIB GLESv2)
else ()
	set(OPENGL_LIB GLESv3)
endif (${ANDROID_PLATFORM_LEVEL} LESS 12)

	set(DOBBY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/dobby/libdobby.a)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(
		restoration
		${LZ_LIB}
		${DOBBY_LIB}
		${OPENGL_LIB}
		${GLESV2_LIB}
		${android}
		${egl}
		${log-lib}
		# curl::curl_static
)