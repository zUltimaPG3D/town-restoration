# town-restoration
Toro and Friends: Onsen Town (english version) patch to reenable game functionality

# NOT SERVER DEPENDENT!
#### (at least currently...)
The English release of Onsen Town depended on servers, and an older (yet recent) revival attempt of Onsen Town was also dependent on servers.

For now, this project will do it's best to make the game playable **without** real server requests being passed.

For a more accurate/secure server, ~~[dewdrop](https://github.com/synzr/dewdrop) is being worked on and~~ [puzzle](https://github.com/synzr/puzzle/) is abandoned yet still an option for at least getting into the main menu.

# Build instructions
If, for whatever reason, you choose not to use the prebuilt releases, or you just wanna experiment with adding things to the mod, you can of course build the project yourself!

To keep things organized, make a folder named `toro-app` on the root of the project, and put the game's APK in the folder with the name `game.apk`.

If you haven't already, build the project with `./gradlew assembleDebug` (or `./gradlew assembleRelease`) or with the Build button in Android Studio.

With [`apktool`](https://apktool.org/), extract the files of both the `game.apk` and the output from the project build.

Essentially, follow the instructions from [PolarImGui install instructions](https://github.com/Polarmods/PolarImGui/tree/main) on how to add the menu to the game *(but instead of the UnityPlayerActivity smali which doesn't exist due to multidex, edit web/apache/sax/app.smali)*, unless it doesn't work.

If there are any issues, contact me @ `55ar.` on Discord and we can discuss the issue further.

# Game server

The servers for the game run entirely locally, as seen in [toro_webserver.h](app/src/main/jni/toro_webserver/toro_webserver.h), and the [puzzle](https://github.com/synzr/puzzle/) repo mentioned above was used as reference for most endpoints.

The server is in no means secure or accurate to how the real API would work, as it's only purpose is to get the game to run correctly, and it runs entirely locally, so any security exploit found would not affect you at all unless you cause it yourself.

The server runs on port `15151`, but it can run on any chosen port as long as the `HTTP_SERVER_URL` define in `Main.cpp` is edited to reflect the change.

# Credits, Dependencies and Libraries
[LGL Mod Menu](https://github.com/LGLTeam/Android-Mod-Menu) by LGLTeam (GPL v3)

[PolarImGui](https://github.com/Polarmods/PolarImGui) by Polarmods (GPL v3)

[ImGui](https://github.com/ocornut/imgui) by ocornut (MIT)

[Il2CppVersions](https://github.com/nneonneo/Il2CppVersions) by nneonneo

[KittyMemory](https://github.com/MJx0/KittyMemory) by MJx0 (MIT)

[xDL](https://github.com/hexhacking/xDL) by hexhacking (MIT)

[Dobby](https://github.com/jmpews/Dobby) by jmpews (Apache 2.0)

[mongoose](https://github.com/cesanta/mongoose) by cesanta (GPL v2)

[puzzle](https://github.com/synzr/puzzle/) by synzr (Apache 2.0)