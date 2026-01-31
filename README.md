# town-restoration
A Toro and Friends: Onsen Town (english version) patch to re-enable game functionality

> ## QUICK SUMMARY
> To self host the game, the mod needs to be compiled manually, and a separate server needs to be ran by the user.
> Read the **build instructions** for the mod below, and also the **server instructions** in the [Saturn](https://github.com/zUltimaPG3D/Saturn) repository (if you're using it).

# Server Dependency
Due to the increase in complexity with the server implementation, the server no longer runs in parallel with the game, but instead is meant to be ran separately from the device.

To run the game, you need a server recreation ([Saturn](https://github.com/zUltimaPG3D/Saturn) is the best option for the time being) that the game can connect to.

# Build instructions
Before building, edit the `Main.cpp` file and replace the `HTTP_SERVER` define with wherever the server is running.

To keep things organized, make a folder named `toro-app` on the root of the project, and put the game's APK in the folder with the name `game.apk`.

If you haven't already, build the project with `./gradlew assembleDebug` (or `./gradlew assembleRelease`) or with the Build button in Android Studio.

With [`apktool`](https://apktool.org/), extract the files of both the `game.apk` and the output from the project build.

Essentially, follow the instructions from [PolarImGui implementation instructions](https://github.com/Polarmods/PolarImGui/tree/main?tab=readme-ov-file#implementation) on how to add the menu to the game *(but instead of the UnityPlayerActivity smali which doesn't exist due to multidex, edit web/apache/sax/app.smali)*, unless it doesn't work.

I personally recommend putting the `loadLibrary` snippet after this line in the app.smali file (should be line 817):
```
invoke-virtual {p0, v0, v1}, Lweb/apache/sax/app;->run(Landroid/content/res/AssetManager;Landroid/os/Handler;)V
```

This is actually a line you have to either comment out or remove, due to it being what starts the AppSolid detections, which make it so the game doesn't start after being edited.

Another thing you have to do is go into `res/xml/network_security_config.xml` and add the domain Saturn is running on, and this should be what the xml file looks like:
```xml
<?xml version="1.0" encoding="utf-8"?>
<network-security-config>
    <domain-config cleartextTrafficPermitted="true">
        <domain includeSubdomains="true">toropuzz.com</domain>
        <domain includeSubdomains="true">bx70.bxlocal</domain>
        <domain includeSubdomains="false">hikari.bexide.jp</domain>
        <domain includeSubdomains="true">toro.ncucu.com</domain>
        <domain includeSubdomains="true">192.168.1.16</domain> <!-- This can be anything else as long as it's the same as HTTP_SERVER! -->
    </domain-config>
</network-security-config>
```

If there are any issues, contact me (@`55ar.` on Discord) and we can discuss the issue further.

# Credits, Dependencies and Libraries
[LGL Mod Menu](https://github.com/LGLTeam/Android-Mod-Menu) by LGLTeam (GPL v3)

[PolarImGui](https://github.com/Polarmods/PolarImGui) by Polarmods (GPL v3)

[ImGui](https://github.com/ocornut/imgui) by ocornut (MIT)

[Il2CppVersions](https://github.com/nneonneo/Il2CppVersions) by nneonneo

[KittyMemory](https://github.com/MJx0/KittyMemory) by MJx0 (MIT)

[xDL](https://github.com/hexhacking/xDL) by hexhacking (MIT)

[Dobby](https://github.com/jmpews/Dobby) by jmpews (Apache 2.0)

[mongoose](https://github.com/cesanta/mongoose) by cesanta (GPL v2)

[puzzle](https://code.autism.net.ru/synzr-archive/puzzle) by synzr (Apache 2.0)
