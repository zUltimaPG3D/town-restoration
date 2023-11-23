cmake_minimum_required(VERSION 3.4.1)

add_library(
		restoration
		SHARED
		Main.cpp
	Substrate/hde64.c
	Substrate/SubstrateDebug.cpp
	Substrate/SubstrateHook.cpp
	Substrate/SubstratePosixMemory.cpp
	Substrate/SymbolFinder.cpp
	KittyMemory/KittyMemory.cpp
	KittyMemory/MemoryPatch.cpp
	KittyMemory/MemoryBackup.cpp
	KittyMemory/KittyUtils.cpp
	And64InlineHook/And64InlineHook.cpp
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
	mongoose/mongoose.c
	# mongoose/src/base64.c
	# mongoose/src/device_dummy.c
	# mongoose/src/device_flash.c
	# mongoose/src/device_stm32h5.c
	# mongoose/src/device_stm32h7.c
	# mongoose/src/dns.c
	# mongoose/src/event.c
	# mongoose/src/fmt.c
	# mongoose/src/fs_fat.c
	# mongoose/src/fs_packed.c
	# mongoose/src/fs_posix.c
	# mongoose/src/fs.c
	# mongoose/src/http.c
	# mongoose/src/iobuf.c
	# mongoose/src/json.c
	# mongoose/src/log.c
	# mongoose/src/md5.c
	# mongoose/src/mqtt.c
	# mongoose/src/net_builtin.c
	# mongoose/src/net.c
	# mongoose/src/ota_dummy.c
	# mongoose/src/ota_flash.c
	# mongoose/src/printf.c
	# mongoose/src/queue.c
	# mongoose/src/rpc.c
	# mongoose/src/sha1.c
	# mongoose/src/sntp.c
	# mongoose/src/sock.c
	# mongoose/src/ssi.c
	# mongoose/src/str.c
	# mongoose/src/timer.c
	# mongoose/src/tls_builtin.c
	# mongoose/src/tls_dummy.c
	# mongoose/src/tls_mbed.c
	# mongoose/src/tls_openssl.c
	# mongoose/src/url.c
	# mongoose/src/util.c
	# mongoose/src/ws.c
)

include_directories(mongoose/src)

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

	# set(DOBBY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(
		restoration
		${LZ_LIB}
		# ${DOBBY_LIB}
		${OPENGL_LIB}
		${GLESV2_LIB}
		${android}
		${egl}
		${log-lib}
		# curl::curl_static
)