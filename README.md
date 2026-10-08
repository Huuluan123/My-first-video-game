# My First Video Game

A small C++ project using the WinBGIm graphics library. The repository contains the game source and a separate harmonic-motion graphics example.

## Project layout

- `src/ball.cpp` — the ball game.
- `examples/physics.cpp` — a harmonic-motion drawing example.
- `scripts/build.ps1` — builds both programs for 32-bit Windows.
- `build/` — generated executables and MinGW runtime DLLs; not committed to Git.

## Requirements

- Windows 10 or newer.
- A 32-bit MinGW-w64 GCC toolchain and `mingw32-make`. The default compiler location used by the build script is `C:\mingw32\bin`.
- A WinBGIm library built for the same 32-bit MinGW toolchain. The official WinBGIm site only provides an old prebuilt library; this project was tested with the community-maintained [WinBGIm-fixed-sort-of fork](https://github.com/Duthomhas/WinBGIm-fixed-sort-of-), rebuilt locally from its source.

### Build WinBGIm

Download and extract the [WinBGIm-fixed-sort-of source](https://github.com/Duthomhas/WinBGIm-fixed-sort-of/archive/refs/heads/master.zip). In PowerShell, set the source directory and build it with the same MinGW compiler that will build this project:

```powershell
$env:Path = 'C:\mingw32\bin;' + $env:Path
$env:WINBGIM_SOURCE_DIR = 'C:\dev\WinBGIm-fixed-sort-of\source'
mingw32-make -C $env:WINBGIM_SOURCE_DIR 'CPPFLAGS=-c -O3 -fno-rtti -fno-exceptions -m32 -Wno-narrowing' libbgi.a
```

The `-Wno-narrowing` option is needed for legacy initializers in the fork when building with recent GCC. The resulting source directory should contain `libbgi.a`, `graphics.h`, and `winbgim.h`.

If MinGW is not in `C:\mingw32\bin`, set its location too:

```powershell
$env:MINGW32_BIN = 'C:\path\to\mingw32\bin'
$env:Path = "$env:MINGW32_BIN;$env:Path"
```

## Build this project

From the repository root, run:

```powershell
.\scripts\build.ps1
```

The script creates `build\ball.exe` and `build\physics.exe`, and copies the required MinGW runtime DLLs into `build\`. Copy the selected executable together with all three DLLs when running it on another Windows computer. No MinGW installation is required on the target computer. The programs are 32-bit; the UCRT runtime is included with Windows 10 and newer.

## Run the game

```powershell
.\build\ball.exe
```

Press any key at the title screen. Use `W`, `A`, `S`, and `D` to move the player; press `Esc` to open the menu.

## Third-party components

WinBGIm is an external dependency and is not vendored in this repository. Review the upstream project's license and terms before redistributing its library or bundled runtime files.
