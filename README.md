# VirtualDJ Loop Roll

This repository contains a VirtualDJ 8 buffer-DSP Loop Roll plugin. The
plugin builds as a loadable Windows DLL when configured with the official
VirtualDJ SDK headers.

## Contents

- `LoopRoll.cpp` / `LoopRoll.h` — Filter Roll plugin implementation with one
  centered bipolar control.
- `Main.cpp` — VirtualDJ COM entry point.
- `VirtualDJAdapter.todo.h` — SDK integration notes.
- `.github/workflows/windows.yml` — Windows workflow that builds and archives
  the DLL.

## Behavior

- The single Filter Roll control is off at its center (`0 ms`). Moving either
  direction selects negative loop lengths from `-400 ms` down to `-20 ms` in
  10 ms increments.
- Loop Roll and filtering are enabled and disabled together.
- Filter processing is bipolar: one side applies a low cut (high-pass),
  the other applies a high cut (low-pass), and the center bypasses filtering.
- Loop capture is aligned to the host's beat grid using `SongPosBeats` and
  `SongBpm`.
- Audio uses the stereo 16-bit buffer contract defined by `vdjDsp8.h`.
- The plugin requires the exact `vdjPlugin8.h` and `vdjDsp8.h` headers for the
  target SDK version; it does not provide guessed SDK declarations.

## Build locally

```powershell
cmake -S . -B build -DVDJ_SDK_DIR="<SDK include directory>"
cmake --build build --config Release
```

The resulting file is `build/Release/rolll.dll`. GitHub Actions downloads the
SDK headers and performs the same build automatically.

Install the 64-bit DLL at:
`%LOCALAPPDATA%\VirtualDJ\Plugins64\SoundEffect\rolll.dll`
