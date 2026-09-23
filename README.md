# VirtualDJ Loop Roll

This repository contains a VirtualDJ 8 buffer-DSP Loop Roll plugin. The
plugin builds as a loadable Windows DLL when configured with the official
VirtualDJ SDK headers.

## Contents

- `LoopRoll.cpp` / `LoopRoll.h` — plugin implementation, strength control, and
  centered millisecond loop-length control.
- `Main.cpp` — VirtualDJ COM entry point.
- `VirtualDJAdapter.todo.h` — SDK integration notes.
- `.github/workflows/windows.yml` — Windows workflow that builds and archives
  the DLL.

## Behavior

- The Length control is off at its center (`0 ms`). Moving either direction
  selects 20 mirrored steps from `10 ms` through `190 ms`, increasing by
  `10 ms` per step.
- Strength controls the dry/wet mix from 0% to 100%.
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
