# VirtualDJ Loop Roll — reconstructed source scaffold

**Status: source scaffold only. This repository does not yet build a loadable VirtualDJ DLL.**

This package contains a host-independent loop-roll DSP prototype and notes for the VirtualDJ SDK adapter. It is prepared for uploading to a new GitHub repository.

## Contents

- `Source/LoopRoll.cpp` — tempo/loop-length prototype.
- `Source/LoopRollEngine.h` — host-independent stereo interleaved float buffer engine.
- `Source/VirtualDJAdapter.todo.h` — integration checklist.
- `.github/workflows/windows.yml` — Windows workflow that validates and archives the scaffold; it does not compile a DLL.

## Important behavior/limitations

- The DSP prototypes assume floating-point audio in the formats documented in their comments. The VirtualDJ adapter must use the exact format and callback contract from the official SDK.
- Grid-accurate capture must be aligned to the host's beat phase/transport position, not merely started when a UI toggle changes.
- Correct post-roll resume behavior depends on the host callback/transport semantics and must be implemented and tested against the SDK.
- `LoopRoll.cpp` currently has no complete VirtualDJ plugin class, parameter registration, or `DllGetClassObject` COM factory.
- Do not add guessed SDK declarations. Obtain the official `vdjPlugin8.h` and `vdjDsp8.h` for the target SDK version and integrate against those exact definitions.

## Upload to a new GitHub repository

1. Create an empty repository on GitHub (do not initialize it with a README or license).
2. Extract this ZIP.
3. Upload the **contents** of the extracted folder to the repository root, preserving `.github/workflows/windows.yml`.
4. Commit to the default branch (the workflow is configured for `main`; change the branch filter if needed).
5. Open **Actions** and run **Windows build**. At this stage it checks and archives the source scaffold only.

## To reach a real DLL

A developer still needs to implement the official VirtualDJ DSP plugin adapter, parameters, COM entry point/class factory, and a real MSVC/CMake build target. Then update the workflow to build and upload the resulting `.dll`. The current workflow intentionally does not pretend that a source archive is a DLL.
