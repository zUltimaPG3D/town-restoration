# town-restoration
Toro and Friends: Onsen Town (english version) patch to reenable game functionality

# NOT SERVER DEPENDENT!
#### (at least currently...)
The English release of Onsen Town depended on servers, and an older (yet recent) revival attempt of Onsen Town was also dependent on servers.

For now, this project will do it's best to make the game playable **without** real server requests being passed.

# Build instructions
If, for whatever reason, you choose not to use the prebuilt releases, or you just wanna experiment with adding things to the mod, you can of course build the project yourself!

To keep things organized, make a folder named `toro-app` on the root of the project, and put the game's APK in the folder with the name `game.apk`.

If you haven't already, build the project with `./gradlew assembleDebug` (or `./gradlew assembleRelease`) or with the Build button in Android Studio.

With [`apktool`](https://apktool.org/), extract the files of both the `game.apk` and the output from the project build.

Essentially, follow the instructions from [PolarImGui install instructions](https://github.com/Polarmods/PolarImGui/tree/main) on how to add the menu to the game *(but instead of the UnityPlayerActivity smali which doesn't exist due to multidex, edit web/apache/sax/app.smali)*, unless it doesn't work.

If there are any issues, contact me @ `55ar.` on Discord and we can discuss the issue further.