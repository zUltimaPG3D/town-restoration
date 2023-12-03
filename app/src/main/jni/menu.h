// #include "imgui/imgui.h"
#include "json.hpp"
#include "lib-utils/LitJson.h"
#include "lib-utils/Delegate.h"
#include "lib-utils/HttpResponse.h"
#include "toro_webserver/toro_webserver.h"
#include "Unity/Screen.h"

bool restart_on_clear = true;
bool owoify_enabled = false;
bool sl_gc = false;

inline void OpenURL(const std::string& url)
{
	((void(*)(il2cppString*))POINTER_NOSEMICOLON("0x19D15D4"))(CreateIl2CppString(url.c_str()));
}

inline void ClearMyData()
{
	((void(*)()) POINTER_NOSEMICOLON("0x19F16B8"))();
	if (restart_on_clear)
		exit(-1);
}

#include "Misc/enums.h"

#include "menu_hook.h"
#include "Unity/Input.h"
#include "KittyMemory/KittyScanner.hpp"
// using namespace ImGui;

using namespace KittyScanner;

#include "Misc/owo-hook/owo.h"

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

il2cppString* (*old_GetDomainURL)(il2cppString* keyName);
il2cppString* GetDomainURL(il2cppString* keyName)
{
	il2cppString* s = old_GetDomainURL(keyName);
	std::string orig = s->getString();
	LOGW("Redirecting %s to localhost", orig.c_str());
	if (!sl_gc) return CreateIl2CppString(HTTP_SERVER_URL); // not good if you're running a blockheads server on the device 🔥
	return s;
}

void (*old_NTDebugLogHook)(void* message);
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

il2cppString* (*old_Encrypt)(il2cppString* uid);
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
	return CreateIl2CppString(HTTP_SERVER_URL);
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

il2cppString* (*old_GameCode)();
il2cppString* GameCode()
{
	if (sl_gc) return CreateIl2CppString("SL");
	return old_GameCode();
}

il2cppString* (*old_TMP_Text$get_text)(void* instance);
il2cppString* TMP_Text$get_text(void* instance)
{
	il2cppString* real = old_TMP_Text$get_text(instance);
	return owoify_enabled ? OwOify(real) : real;
}

il2cppString* (*old_Text$get_text)(void* instance);
il2cppString* Text$get_text(void* instance)
{
	il2cppString* real = old_Text$get_text(instance);
	return owoify_enabled ? OwOify(real) : real;
}

void (*old_BXTrackEvent)(il2cppString* s);
void BXTrackEvent(il2cppString* s)
{
	LOGW("BX.AdjustCall TrackEvent(string) with %s", s->getString().c_str());
	old_BXTrackEvent(s);
}

il2cppString* Serialize(void* object)
{
	// other possible serialize options:
	// IronSource JSON Serialize - 0x2CEC978
	// MiniJson JSON Serialize - 0x1118B18
	// Unity SimpleJson Serialize - 0x2B3C5E0
	// LitJson JsonMapper Serialize - 0x26A3C70
	return ((il2cppString* (*) (void*)) POINTER_NOSEMICOLON("0x26A3C70"))(object);
}

void (*old_AnalyticsSendLog)(int action, il2cppArray<void**>* paramList);
void AnalyticsSendLog(int action, il2cppArray<void**>* paramList)
{
	std::string i_hate_fmt = "Analytics.SendLog(ToroLogType, object[]) for action " + std::to_string(action);
	LOGW("%s", i_hate_fmt.c_str());
	LOGW("Is params null / empty? %s", (paramList == nullptr) ? "Yes" : "No");
	old_AnalyticsSendLog(action, paramList);
}

void (*old_EventLogin)(int x);
void EventLogin(int x)
{
	std::string i_hate_fmt = "Analytics.EventLogin(PlatformID) for pid " + std::to_string(x);
	LOGW("%s", i_hate_fmt.c_str());
	old_EventLogin(x);
}

void (*old_EventTOS)();
void EventTOS()
{
	std::string i_hate_fmt = "Analytics.EventTOS()";
	LOGW("%s", i_hate_fmt.c_str());
	old_EventTOS();
}

void (*old_EventFirstLogin)();
void EventFirstLogin()
{
	std::string i_hate_fmt = "Analytics.EventFirstLogin()";
	LOGW("%s", i_hate_fmt.c_str());
	old_EventFirstLogin();
}

void (*old_NTPlayerPrefs_SetString)(void* instance, il2cppString* key, il2cppString* value);
void NTPlayerPrefs_SetString(void* instance, il2cppString* key, il2cppString* value)
{
	LOGW("NTPlayerPrefs.SetString(%s, %s)", key->getString().c_str(), value->getString().c_str());
	old_NTPlayerPrefs_SetString(instance, key, value);
}

void* (*old_CoShowTerms)(void* observer, il2cppArray<int*>* termsType, il2cppString platformUserId, il2cppArray<bool*>* initialValues);
void* CoShowTerms(void* observer, il2cppArray<int*>* termsType, il2cppString platformUserId, il2cppArray<bool*>* initialValues)
{
	LOGW("CoShowTerms");
	return old_CoShowTerms(observer, termsType, platformUserId, initialValues);
}

void* (*old_RequestAsObservable)(il2cppString* serverAddr, il2cppString* act, void* param, void* webData, void* preprocessor, void* postprocessor);
void* RequestAsObservable(il2cppString* serverAddr, il2cppString* act, void* param, void* webData, void* preprocessor, void* postprocessor)
{
	LOGW("RequestAsObservable");
	return old_RequestAsObservable(CreateIl2CppString(HTTP_SERVER_URL), act, param, webData, preprocessor, postprocessor);
}

void hooks()
{
	HOOK("0xC1C7C0", GetDomainURL, old_GetDomainURL);
	HOOK("0xC1BBFC", GameCode, old_GameCode);
	HOOK("0x2ABF7D0", Encrypt, old_Encrypt);
	HOOK("0x2ABF7D0", Decrypt, old_Decrypt);
	HOOK("0xA0DC70", TMP_Text$get_text, old_TMP_Text$get_text);
	HOOK("0x15C0CCC", Text$get_text, old_Text$get_text);
	HOOK("0x2BE2914", BXTrackEvent, old_BXTrackEvent);
	HOOK("0x2BD8118", AnalyticsSendLog, old_AnalyticsSendLog);
	HOOK("0x2BE3998", EventLogin, old_EventLogin);
	HOOK("0x2BE2804", EventTOS, old_EventTOS);
	HOOK("0x2BE3780", EventFirstLogin, old_EventFirstLogin);
	HOOK("0x26D6500", NTPlayerPrefs_SetString, old_NTPlayerPrefs_SetString);
	HOOK("0xD2D65C", CoShowTerms, old_CoShowTerms);
	HOOK("0xD2AB84", RequestAsObservable, old_RequestAsObservable);
	//HOOK_NO_ORIG("0xC1F3E4", CommonAPI$$IsDev);
	//HOOK("0x2AF74B0", termsTask, old_termsTask);
	//HOOK("0x2AF7D08", loginTask, old_loginTask);
	//HOOK("0x2AF82DC", oauthConnectTask, old_oauthConnectTask);
	//HOOK("0x2868EE8", DoLogin, old_DoLogin);
	//HOOK("0x2CADFAC", LineSDKListener$$OnRegisterToken, old_LineSDKListener$$OnRegisterToken);
	//HOOK("0x2868994", GetLoginUrl, old_GetLoginUrl);
	//HOOK("0x270F134", temp, old_temp);
	//HOOK_NO_ORIG("0x2867180", IsDummy);
	//HOOK("0x270EAF0", PushAPI$$__Internal$$OnRegisterToken, old_PushAPI$$__Internal$$OnRegisterToken);
	//HOOK("0xC23964", CommonAPI$$__Internal$$OnRegisterToken, old_CommonAPI$$__Internal$$OnRegisterToken);
	//HOOK_NO_ORIG("0xF9A7B4", m_current_url);
	//HOOK("0x2712FCC", Post, old_Post);
	//HOOK("0x2712FCC", NONOBSERVABLE_Post, old_NONOBSERVABLE_Post);
	//HOOK("0xD2A188", NTException$$_ctor, old_NTException$$_ctor);
	//HOOK("0x26D2DC8", NTDebugLogHook, old_NTDebugLogHook);
	//HOOK_NO_ORIG("0x26D2DD0", WarningNTDebugLogHook);
	//HOOK_NO_ORIG("0x26D2DCC", ErrorNTDebugLogHook);
}

int (*old_ntsdk_login_guest)(char *s, int a2, int a3);
int ntsdk_login_guest(char *s, int a2, int a3)
{
	LOGW("native ntsdk_login_guest");
	old_ntsdk_login_guest(s, a2, a3);
}

void ntsdk_hook()
{
	HOOKSYM_LIB("lib_NTSDK.so", "ntsdk_login_guest", ntsdk_login_guest, old_ntsdk_login_guest);
}

void ntsdk_wait()
{
	do {
		ntsdkMap = KittyMemory::getElfBaseMap("lib_NTSDK.so");
	} while (!ntsdkMap.isValid());
	LOGI("lib_NTSDK has been loaded");
	ntsdk_hook();
}

void *hack_thread(void *) {
	LOGI("pthread created");

	//Check if target lib is loaded
	do {
		sleep(1);
		il2cppMap = KittyMemory::getElfBaseMap(targetLibName);
	} while (!il2cppMap.isValid());
	do {
		unityMaps = KittyMemory::getMapsEndWith("libunity.so");
	} while (unityMaps.empty());
	std::thread(&ntsdk_wait).detach(); // runs on a separate thread as to not pause the menu loading (which causes issues!!)

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
		LOGE("il2cpp initialized");
	} else {
		LOGE("failed to initialize il2cpp.");
	}

	hook_menu_stuff();

	UnityEngine::Screen::Setup();
	RegisterNativeFn injecteventptr = KittyScanner::findRegisterNativeFn(unityMaps, "nativeInjectEvent");
	if (injecteventptr.isValid()) {
		DobbyHook(injecteventptr.fnPtr, (void *) nativeInjectEvent, (void **) &old_nativeInjectEvent);
	} else {
		UnityEngine::Input::Setup();
	}

	pointers();
	hooks();

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