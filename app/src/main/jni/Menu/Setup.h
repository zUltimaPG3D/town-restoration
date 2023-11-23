#include <sstream>
#include "Menu.h"
#include "get_device_api_level_inlines.h"

//Jni stuff from MrDarkRX https://github.com/MrDarkRXx/DarkMod-Floating
void setDialog(jobject ctx, JNIEnv *env, const char *title, const char *msg){
    jclass Alert = env->FindClass("android/app/AlertDialog$Builder");
    jmethodID AlertCons = env->GetMethodID(Alert, "<init>", "(Landroid/content/Context;)V");

    jobject MainAlert = env->NewObject(Alert, AlertCons, ctx);

    jmethodID setTitle = env->GetMethodID(Alert, "setTitle", "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(MainAlert, setTitle, env->NewStringUTF(title));

    jmethodID setMsg = env->GetMethodID(Alert, "setMessage", "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(MainAlert, setMsg, env->NewStringUTF(msg));

    jmethodID setCa = env->GetMethodID(Alert, "setCancelable", "(Z)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(MainAlert, setCa, false);

    jmethodID setPB = env->GetMethodID(Alert, "setPositiveButton", "(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(MainAlert, setPB, env->NewStringUTF("Ok"), static_cast<jobject>(NULL));

    jmethodID create = env->GetMethodID(Alert, "create", "()Landroid/app/AlertDialog;");
    jobject creaetob = env->CallObjectMethod(MainAlert, create);

    jclass AlertN = env->FindClass("android/app/AlertDialog");

    jmethodID show = env->GetMethodID(AlertN, "show", "()V");
    env->CallVoidMethod(creaetob, show);
}

void Toast(JNIEnv *env, jobject thiz, const char *text, int length) {
    jstring jstr = env->NewStringUTF(text);
    jclass toast = env->FindClass("android/widget/Toast");
    jmethodID methodMakeText =env->GetStaticMethodID(toast,"makeText","(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
    jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText,thiz, jstr, length);
    jmethodID methodShow = env->GetMethodID(toast, "show", "()V");
    env->CallVoidMethod(toastobj, methodShow);
}

void startActivityPermisson(JNIEnv *env, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jmethodID startActivity = env->GetMethodID(native_context, "startActivity","(Landroid/content/Intent;)V");

    jmethodID pack = env->GetMethodID(native_context, "getPackageName","()Ljava/lang/String;");
    jstring packageName = static_cast<jstring>(env->CallObjectMethod(ctx, pack));

    const char *pkg = env->GetStringUTFChars(packageName, 0);

    std::stringstream pkgg;
    pkgg << "package:";
    pkgg << pkg;
    std::string pakg = pkgg.str();

    jclass Uri = env->FindClass("android/net/Uri");
    jmethodID Parce = env->GetStaticMethodID(Uri, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    jobject UriMethod = env->CallStaticObjectMethod(Uri, Parce, env->NewStringUTF(pakg.c_str()));

    jclass intentclass = env->FindClass("android/content/Intent");
    jmethodID newIntent = env->GetMethodID(intentclass, "<init>", "(Ljava/lang/String;Landroid/net/Uri;)V");
    jobject intent = env->NewObject(intentclass,newIntent,env->NewStringUTF("android.settings.action.MANAGE_OVERLAY_PERMISSION"), UriMethod);

    env->CallVoidMethod(ctx, startActivity, intent);
}

void startService(JNIEnv *env, jobject ctx){
    jclass native_context = env->GetObjectClass(ctx);
    jclass intentClass = env->FindClass("android/content/Intent");
    jclass actionString = env->FindClass("com/android/support/Launcher");
    jmethodID newIntent = env->GetMethodID(intentClass, "<init>", "(Landroid/content/Context;Ljava/lang/Class;)V");
    jobject intent = env->NewObject(intentClass,newIntent,ctx,actionString);
    jmethodID startActivityMethodId = env->GetMethodID(native_context, "startService", "(Landroid/content/Intent;)Landroid/content/ComponentName;");
    env->CallObjectMethod(ctx, startActivityMethodId, intent);
}

void *exit_thread(void *) {
    sleep(5);
    exit(0);
}

//Needed jclass parameter because this is a static java method
void CheckOverlayPermission(JNIEnv *env, jclass thiz, jobject ctx){
    //If overlay permission option is greyed out, make sure to add android.permission.SYSTEM_ALERT_WINDOW in manifest

    LOGI(OBFUSCATE("Check overlay permission"));

    int sdkVer = api_level();
    if (sdkVer >= 23){ //Android 6.0
        jclass Settings = env->FindClass("android/provider/Settings");
        jmethodID canDraw =env->GetStaticMethodID(Settings, "canDrawOverlays", "(Landroid/content/Context;)Z");
        if (!env->CallStaticBooleanMethod(Settings, canDraw, ctx)){
            Toast(env,ctx,"Overlay permission is required in order to show mod menu.",1);
            Toast(env,ctx,"Overlay permission is required in order to show mod menu.",1);
            startActivityPermisson(env, ctx);

            pthread_t ptid;
            pthread_create(&ptid, NULL, exit_thread, NULL);
            return;
        }
    }


    LOGI("Start service");

    //StartMod Normal
    startService(env, ctx);
}

void Init(JNIEnv *env, jobject thiz, jobject ctx, jobject title, jobject subtitle){
    //Set sub title
    setText(env, title, "<b>Town Restoration</b>");

    //Set sub title
    /*setText(env, subtitle, OBFUSCATE("<b><marquee><p style=\"font-size:30\">"
                                     "<p style=\"color:green;\">Honest message to APPSOLID:</p> | "
                                     "Get better. Get better at actually protecting against tampering, because, honestly, all it took to bypass it was commenting out one single line in the app.smali file. As confusing as both the smali and libmm are, I still cannot believe it's that easy to bypass your stupi</p>"
                                     "</marquee></b>"));*/

    //Dialog Example
    //setDialog(ctx,env,OBFUSCATE("Title"),OBFUSCATE("Message Example"));

    //Toast Example
    Toast(env,ctx,"Mod loaded successfully!",ToastLength::LENGTH_LONG);

    initValid = true;
}