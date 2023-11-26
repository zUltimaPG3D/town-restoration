// #include "imgui/imgui.h"
#include "json.hpp"
#include "lib-utils/LitJson.h"
#include "lib-utils/Delegate.h"
#include "lib-utils/HttpResponse.h"
#include "toro_webserver/toro_webserver.h"
// using namespace ImGui;

long idx = 0;
#define STEP() idx++; LOGE("%l", idx)

bool step1 = true, step2 = true, step3 = true, step4 = true, step5 = true, step6 = true;

void (*LineSDKListener$$OnGameLanguage)(void* instance, Il2CppArray* supportLanguages, void* error);
void (*LineSDKListener$$OnGameServerList)(void* instance, void* result, void* error);
void (*LineSDKListener$$OnGetVersion)(void* instance, void* result, void* error);
void (*LineSDKListener$$OnInitialized)(void* instance);
void (*NetManager_VersionCallback)(void* instance, void* response);
il2cppString* (*ToString)(void* object);
void* (*LineSDKManager$$get_SDKListener)();
int (*get_Screen$$Width)();
int (*get_Screen$$Height)();

//bool (*old_CommonAPI$$IsDev)();
bool CommonAPI$$IsDev()
{
	LOGI("IsDev checked!");
	return true;
}

#define get_SDKListener LineSDKManager$$get_SDKListener()

void* (*old_Post)(il2cppString* url, void* param, void* webData);
void* Post(il2cppString* url, void* param, void* webData)
{
	std::string urlString = url->getString();
	LOGI("Observable request to %s sent", urlString.c_str());
	return old_Post(url, param, webData);
}

void (*old_NONOBSERVABLE_Post)(il2cppString* url, void* param, void* webData, void* callback);
void NONOBSERVABLE_Post(il2cppString* url, void* param, void* webData, void* callback)
{
	std::string urlString = url->getString();
	LOGI("Request to %s sent", urlString.c_str());
	return old_NONOBSERVABLE_Post(url, param, webData, callback);
}

void* (*old_termsTask)(void* instance);
void* termsTask(void* instance)
{
	LOGI("termsTask: CALLED");
	return old_termsTask(instance);
}

void* (*old_loginTask)(void* instance);
void* loginTask(void* instance)
{
	LOGI("loginTask: CALLED");
	return old_loginTask(instance);
}

void* (*old_oauthConnectTask)(void* instance);
void* oauthConnectTask(void* instance)
{
	LOGI("oauthConnectTask: CALLED");
	return old_oauthConnectTask(instance);
}

void* (*old_LineSDKListener$$OnRegisterToken)(void* instance, void* rpt, void* exc);
void* LineSDKListener$$OnRegisterToken(void* instance, void* rpt, void* exc)
{
	LOGE("LineSDKListener.OnRegisterToken: CALLED");
	return old_LineSDKListener$$OnRegisterToken(instance, rpt, exc);
}

il2cppString* GetDomainURL(il2cppString* keyName)
{
	LOGW("Redirecting DomainURL(%s) to localhost", keyName->getString().c_str());
	return CreateIl2CppString("http://localhost:15151/"); // not good if you're running a blockheads server on the device 🔥
}

void NTDebugLogHook(void* message)
{
	((void(*)(void*))POINTER_NOSEMICOLON("0x11D8160"))(message);
}

void WarningNTDebugLogHook(void* message)
{
	((void(*)(void*))POINTER_NOSEMICOLON("0x11D0D4C"))(message);
}

void ErrorNTDebugLogHook(void* message)
{
	((void(*)(void*))POINTER_NOSEMICOLON("0x11D85E4"))(message);
}

int glHeight, glWidth;
bool init = false;

/*void InitImGUI()
{
	IMGUI_CHECKVERSION();
	CreateContext();
	ImGui_ImplOpenGL3_Init("#version 100");
	ImGuiIO &io = GetIO();
	io.DisplaySize = ImVec2(get_Screen$$Width(), get_Screen$$Height());
	// ImGui_ImplAndroid_Init(nullptr);
	SetupImGuiStyle();
	GetStyle().ScaleAllSizes(4.0f);
}*/

/*EGLBoolean (*old_eglSwapBuffers)(EGLDisplay display, EGLSurface surface);
EGLBoolean eglSwapBuffers(EGLDisplay display, EGLSurface surface)
{
	if (!init)
	{
		STEP();
		InitImGUI();
		STEP();
		init = true;
	}
	STEP();
	ImGuiIO &io = GetIO();
	STEP();
	if (step1)
		ImGui_ImplOpenGL3_NewFrame();
	STEP();
	if (step2)
		NewFrame();
	STEP();
	if (step3)
		DrawMenu();
	STEP();
	if (step4)
		EndFrame();
	STEP();
	if (step5)
		Render();
	STEP();
	if (step6)
		ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
	STEP();
	return old_eglSwapBuffers(display, surface);
}*/

/*void* (*old_NetManager$$__c$$_ctor)(void* instance);
void* NetManager$$__c$$_ctor(void* instance)
{
	NetManagerWeirdClass = instance;
	return old_NetManager$$__c$$_ctor(instance);
}*/

bool IsDummy(void* instance)
{
	return true;
}

bool IsGetVersionInfo()
{
	return true;
}

void pointers()
{
	get_Screen$$Width = (int (*)()) POINTER("0x1B884DC");
	get_Screen$$Height = (int (*)()) POINTER("0x1B88560");
	LineSDKListener$$OnGameLanguage = (void (*)(void*, Il2CppArray*, void*)) POINTER("0x2CACED4");
	LineSDKListener$$OnGameServerList = (void (*)(void*, void*, void*)) POINTER("0x2CACEF4");
	LineSDKListener$$OnGetVersion = (void (*)(void*, void*, void*)) POINTER("0x2CAD2AC");
	LineSDKManager$$get_SDKListener = (void* (*)()) POINTER("0x2CAF084");
	ToString = (il2cppString*(*)(void*)) POINTER("0x1183924");
	NetManager_VersionCallback = (void(*)(void*,void*)) POINTER("0x2A84448");
	litjson_pointers();
}

il2cppString* Encrypt(il2cppString* uid)
{
	LOGW("Game tried to encrypt string %s!", uid->getString().c_str());
	return uid;
}

il2cppString* (*old_Decrypt)(il2cppString* src);
il2cppString* Decrypt(il2cppString* src)
{
	il2cppString* dec_src = old_Decrypt(src);
	LOGW("Game tried to decrypt string %s!", src->getString().c_str());
	LOGW("Decrypted string result: %s", dec_src->getString().c_str());
	return dec_src;
}

void* (*old_NTException$$_ctor)(void* instance, int result, il2cppString* message);
void* NTException$$_ctor(void* instance, int result, il2cppString* message)
{
	LOGW("Thrown NTException with message: %s", message->getString().c_str());
	return old_NTException$$_ctor(instance, result, message);
}

void (*old_PushAPI$$__Internal$$OnRegisterToken)(bool success, il2cppString* pushToken);
void PushAPI$$__Internal$$OnRegisterToken(bool success, il2cppString* pushToken)
{
	LOGE("PushAPI OnRegisterToken call, pushToken %s, success %s", pushToken->getString().c_str(), (success ? "Y" : "N"));
	return old_PushAPI$$__Internal$$OnRegisterToken(success, pushToken);
}

void (*old_CommonAPI$$__Internal$$OnRegisterToken)(il2cppString* pushToken);
void CommonAPI$$__Internal$$OnRegisterToken(il2cppString* pushToken)
{
	LOGE("CommonAPI OnRegisterToken call, pushToken %s", pushToken->getString().c_str());
	return old_CommonAPI$$__Internal$$OnRegisterToken(pushToken);
}

il2cppString* m_current_url()
{
	return CreateIl2CppString("http://localhost:15151/");
}

void* (*old_DoLogin)(bool t);
void* DoLogin(bool t)
{
	LOGW("netmanager do login ()");
	return old_DoLogin(t);
}

il2cppString* (*old_GetLoginUrl)(int t);
il2cppString* GetLoginUrl(int t)
{
	il2cppString* orig = old_GetLoginUrl(t);
	LOGW("getloginurl %s", orig->getString().c_str());
	return orig;
}

void* (*old_temp)(void* instance, il2cppString* params);
void* temp(void* instance, il2cppString* params)
{
	LOGE("PushProcessor OnRegisterToken: CALLED");
	return old_temp(instance, params);
}

void hooks()
{
	HOOK_NO_ORIG("0xC1C7C0", GetDomainURL);
	HOOK_NO_ORIG("0x2ABF7D0", Encrypt);
	HOOK("0x2ABF7D0", Decrypt, old_Decrypt);
	HOOK_NO_ORIG("0xC1F3E4", CommonAPI$$IsDev);
	HOOK("0x2AF74B0", termsTask, old_termsTask);
	HOOK("0x2AF7D08", loginTask, old_loginTask);
	HOOK("0x2AF82DC", oauthConnectTask, old_oauthConnectTask);
	HOOK("0x2868EE8", DoLogin, old_DoLogin);
	HOOK("0x2CADFAC", LineSDKListener$$OnRegisterToken, old_LineSDKListener$$OnRegisterToken);
	HOOK("0x2868994", GetLoginUrl, old_GetLoginUrl);
	HOOK("0x270F134", temp, old_temp);
	//HOOK_NO_ORIG("0x2867180", IsDummy);
	HOOK("0x270EAF0", PushAPI$$__Internal$$OnRegisterToken, old_PushAPI$$__Internal$$OnRegisterToken);
	HOOK("0xC23964", CommonAPI$$__Internal$$OnRegisterToken, old_CommonAPI$$__Internal$$OnRegisterToken);
	HOOK_NO_ORIG("0xF9A7B4", m_current_url);
	HOOK("0x2712FCC", Post, old_Post);
	HOOK("0x2712FCC", NONOBSERVABLE_Post, old_NONOBSERVABLE_Post);
	HOOK("0xD2A188", NTException$$_ctor, old_NTException$$_ctor);
	HOOK_NO_ORIG("0x26D2DC8", NTDebugLogHook);
	//HOOK_NO_ORIG("0x26D2DD0", WarningNTDebugLogHook);
	//HOOK_NO_ORIG("0x26D2DCC", ErrorNTDebugLogHook);
}

void *hack_thread(void *) {
	LOGI("pthread created");

	//Check if target lib is loaded
	do {
		sleep(1);
	} while (!isLibraryLoaded(targetLibName));

	LOGI("%s has been loaded", (const char *) targetLibName);
	auto il2cpp_handle = xdl_open("libil2cpp.so", 0);
	init_il2cpp_api(il2cpp_handle);
	if (il2cpp_domain_get_assemblies != nullptr) {

		Dl_info dlInfo;
		if (dladdr((void *) il2cpp_domain_get_assemblies, &dlInfo)) {
			il2cpp_base = reinterpret_cast<uint64_t>(dlInfo.dli_fbase);
		}

		while (!il2cpp_is_vm_thread(nullptr)) {
			sleep(1);
		}

		domain = il2cpp_domain_get();
		il2cpp_thread_attach(domain);
		LibImages.mscorlib = il2cpp_get_corlib();
		libs = il2cpp_domain_get_assemblies(domain, &libCount);

		for (int i = 0; i < libCount; ++i) {
			const Il2CppImage *img = il2cpp_assembly_get_image(libs[i]);
			const char *img_name = il2cpp_image_get_name(img);
			if (strcmp(img_name, "Assembly-CSharp.dll") == 0) {
				LibImages.Assembly_CSharp = img;
			}
			if (strcmp(img_name, "Neptune.Core.dll") == 0) {
				LibImages.Neptune_Core = img;
			}
			if (strcmp(img_name, "LitJson.dll") == 0) {
				LibImages.LitJson = img;
			}
			if (strcmp(img_name, "UnityEngine.CoreModule.dll") == 0) {
				LibImages.UnityCoreModule = img;
			}
		}

		DEFAULTS_INIT(Byte, "System", "Byte");
		DEFAULTS_INIT(Int16, "System", "Int16");
		DEFAULTS_INIT(Int32, "System", "Int32");
		DEFAULTS_INIT(Int64, "System", "Int64");
		DEFAULTS_INIT(Float, "System", "Single");
		DEFAULTS_INIT(Double, "System", "Double");
		DEFAULTS_INIT(Char, "System", "Char");
		DEFAULTS_INIT(String, "System", "String");
		DEFAULTS_INIT(Object, "System", "Object");
		DEFAULTS_INIT(Array, "System", "Array");

	} else {
		LOGE("failed to initialize il2cpp.");
	}

	pointers();
	hooks();

	// HOOKSYM_LIB("libEGL.so", "eglSwapBuffers", eglSwapBuffers, old_eglSwapBuffers);
	/*auto eglhandle = dlopen("libEGL.so", RTLD_LAZY);
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
		hook(eglSwapBuffers, (void *) eglSwapBuffers, (void **) &old_eglSwapBuffers);
	}*/

	// examples, just in case:
	// HOOK("str", FunctionExample, old_FunctionExample);
	// HOOK_LIB("libFileB.so", "0x123456", FunctionExample, old_FunctionExample);
	// HOOK_NO_ORIG("0x123456", FunctionExample);
	// HOOK_LIB_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
	// HOOKSYM("__SymbolNameExample", FunctionExample, old_FunctionExample);
	// HOOKSYM_LIB("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
	// HOOKSYM_NO_ORIG("__SymbolNameExample", FunctionExample);
	// HOOKSYM_LIB_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);

	// PATCH("0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
	// PATCH_LIB("libFileB.so", "0x20D3A8", "00 00 A0 E3 1E FF 2F E1");

	// RESTORE("0x20D3A8");
	// RESTORE_LIB("libFileB.so", "0x20D3A8");

	// AddMoneyExample = (void (*)(void *, int)) getAbsoluteAddress(targetLibName, 0x123456);

	init_toro_webserver();

	LOGI("Done");

	return NULL;
}

/*
void DrawMenu()
{
	bool t = true;
	ShowDemoWindow(&t);
}

void SetupImGuiStyle()
{
	// Fork of Classic Steam style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();
	
	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 0.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
	
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.2862745225429535f, 0.3372549116611481f, 0.2588235437870026f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.2862745225429535f, 0.3372549116611481f, 0.2588235437870026f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.5f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.1372549086809158f, 0.1568627506494522f, 0.1098039224743843f, 0.5199999809265137f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2666666805744171f, 0.2980392277240753f, 0.2274509817361832f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2980392277240753f, 0.3372549116611481f, 0.2588235437870026f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2862745225429535f, 0.3372549116611481f, 0.2588235437870026f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.2784313857555389f, 0.3176470696926117f, 0.239215686917305f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.2470588237047195f, 0.2980392277240753f, 0.2196078449487686f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.2274509817361832f, 0.2666666805744171f, 0.2078431397676468f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.5f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.2862745225429535f, 0.3372549116611481f, 0.2588235437870026f, 0.4000000059604645f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.5f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 0.6000000238418579f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.5f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.1372549086809158f, 0.1568627506494522f, 0.1098039224743843f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1882352977991104f, 0.2274509817361832f, 0.1764705926179886f, 0.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.7799999713897705f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.7764706015586853f, 0.2784313857555389f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.729411780834198f, 0.6666666865348816f, 0.239215686917305f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}
*/