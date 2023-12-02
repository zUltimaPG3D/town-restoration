#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_android.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "frontend.h"

EGLBoolean (*old_eglSwapBuffers)(...);
EGLBoolean new_eglSwapBuffers(EGLDisplay _display, EGLSurface _surface) {
	SetupImGui();
	Menu::DrawImGui();
	return old_eglSwapBuffers(_display, _surface);
}

void hook_menu_stuff()
{
	auto eglhandle = dlopen("libEGL.so", RTLD_LAZY);
	const char *dlopen_error = dlerror();
	if (dlopen_error)
	{
		eglhandle = dlopen("libunity.so", RTLD_LAZY);
	}
	auto eglSwapBuffers = dlsym(eglhandle, "eglSwapBuffers");
	const char *dlsym_error = dlerror();
	if (dlsym_error)
	{
		LOGE("Cannot load symbol 'eglSwapBuffers': %s", dlsym_error);
	} else
	{
		hook(eglSwapBuffers, (void *) new_eglSwapBuffers, (void **) &old_eglSwapBuffers);
	}
}