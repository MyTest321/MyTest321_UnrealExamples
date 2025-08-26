# Unreal Cpp
- Jason Tutorial: https://www.youtube.com/watch?v=JYr0auU4HEw&list=PLeGk08zVu457Bkp3EYRqTP0QHue9T0drG

## How to Build

### Build on Windows

### Requirements

- Unreal Editor 5.0.3
- Visual Studio 2022
- .NET Core 3.1 Runtime
- MSVC v143 - VS 2022 C++ x64/x86 build tool (v14.38-17.8)
```
gen_vs2022.bat
```
- Open Visual Studio project `Unreal_Cpp.sln`
- When you open your first Unreal Engine C++ project in VS, you might see a missing-components warning in the **Solution Explorer**. Click **Install** to allow VS to install any additional components necessary for your project

## Tech
- All logic is done by C++
- string formatting by [libfmt](https://github.com/fmtlib/fmt) for better type-safety
