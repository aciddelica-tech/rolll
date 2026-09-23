ROLLL v2.0.0

This is the replacement source set for the VirtualDJ Loop Roll plugin.

Changes:
- Real VirtualDJ skin interface from OnGetUserInterface().
- Eight Loop Roll lengths: 1/32, 1/16, 1/8, 1/4, 1/2, 1, 2, 4 beats.
- The length is registered as a VirtualDJ plugin parameter and is controllable from the skin.
- SongBpm is used as documented by vdjDsp8.h: samples between beats.
- SongPos is used directly for sample-accurate grid alignment.
- The old unused length_ integer and incorrect 3/4 option are removed.

Build:
cmake -S . -B build -DVDJ_SDK_DIR="<SDK include directory>"
cmake --build build --config Release

Output: build/Release/rolll.dll

Install for VirtualDJ 64-bit:
%LOCALAPPDATA%\VirtualDJ\Plugins64\SoundEffect\rolll.dll
