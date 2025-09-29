# Unreal Camera

## How to Build

### Build on Windows

### Requirements

- Unreal Editor 5.5.4
- Visual Studio 2022
```
gen_vs2022.bat
```
- Open Visual Studio project `Unreal_Camera.sln`
- When you open your first Unreal Engine C++ project in VS, you might see a missing-components warning in the **Solution Explorer**. Click **Install** to allow VS to install any additional components necessary for your project

## Tech
- All logic is done by C++
- string formatting by [libfmt](https://github.com/fmtlib/fmt) for better type-safety
