# GDExtension - CMake Template
Build GDExtension with CMake.

> Thanks to [vorlac](https://github.com/vorlac) for the detailed guide how to build GDExtensions with CMake.  
> Check his work here: https://github.com/vorlac/godot-gdextension-demo-cmake

## HOW TO BUILD

1. Open the project folder in Visual Studio.
2. Select the configuration `x64 Release`.
3. Let Visual Studio configure the project.
4. Select the Startup Item `TemplateName.dll`.
5. Build the project.
6. Copy the contents of the `demo/addons` folder into your project.

The extension will be built against the Godot 4.2 release and it should work just fine with Godot 4.3 but not 4.1.  
Open `CMakeLists.txt` and replace `godot-4.2-stable` to build against a different version of Godot.

## HOW TO DEBUG

You can debug GDExtension with the released version of Godot or with the custom build. The latter helps trace bugs directly into the engine.

The routine is also a bit different whether you want to debug the tools code or the game code. Godot runs the game code in a separate process so you need to attach the debugger to that process.

### DEBUG WITH THE RELEASED VERSION OF GODOT

1. Open `.vs/launch.vs.json` file and replace `C:\\Development\\Godot\\Godot_v4.2.1-stable_win64_console.exe` with your path.
2. Open the project folder in Visual Studio.
3. Select the configuration `x64 Debug`.
4. Let Visual Studio configure the project.
5. Select the Startup Item `TemplateName (Godot 4.2)`.

**TO DEBUG TOOLS**

6. Start Debugging (F5).

If everything worked correctly, the editor should automatically open the demo project.

**TO DEBUG GAME**

6. Start Without Debugging (Ctrl+F5). The editor should open the demo project.
7. Play the Project in Godot (F5).
8. Return to Visual Studio and select `Debug > Attach to Process (Ctrl + Alt + P)`.
9. Select the process `Godot_v4.2.1-stable_win64.exe`, the first one, and press the Attach button.

### DEBUG WITH THE CUSTOM BUILD

1. Open the project folder in Visual Studio.
2. Select the configuration `x64 Debug`.
3. Let Visual Studio configure the project.
4. Select the Startup Item `TemplateName (Custom 4.2)`.

**TO DEBUG TOOLS**

5. Start Debugging (F5).

If everything worked correctly, the editor should automatically open the demo project.

**TO DEBUG GAME**

5. Start Without Debugging (Ctrl+F5). The editor should open the demo project.
6. Play the Project in Godot (F5).
7. Return to Visual Studio and select `Debug > Attach to Process (Ctrl + Alt + P)`.
8. Select the process `Godot_v4.2.1-stable_win64.exe`, the first one, and press the Attach button.

## HOW TO BUILD GODOT

To debug with the custom build of Godot, you need to build Godot first. Don't worry, that is easy and it takes just 5 minutes to build the entire engine.

1. Install Python 3.
2. Run `x86_x64 Cross Tools Command Prompt for VS 2022` as administrator.
3. Change directory to Godot folder. E.g. `cd /d E:\gdextension-cmake-template\godot`
4. Install scons: `pip install scons`
5. Edit `.gitmodules` if you want to use a different branch of the engine. The current one is 4.2.
6. Initialize Godot submodule: `git submodule update --init`
7. Build Godot: `scons --directory=godot platform=windows target=editor arch=x86_64 debug_symbols=yes optimize=debug`

## MISC

### CREATE A REPOSITORY FOR GDEXTENSION FROM SCRATCH

1. mkdir myextension
2. cd myextension
3. git init
4. git submodule add -b 4.2 https://github.com/godotengine/godot
5. git config -f .gitmodules submodule.godot.shallow true
6. git submodule update --init
7. copy .vs, demo, src, .gitignore, CMakeLists.txt, CMakePresets.json, LICENSE, README.md
