#pragma once

// Adapter TODOs for the official VirtualDJ SDK:
// 1. Include the actual vdjPlugin8.h and vdjDsp8.h from the SDK.
// 2. Implement the correct IVdjPluginBufferDsp8-derived class.
// 3. Implement OnGetSongBuffer(songPos, nb) using SDK-defined sample format,
//    channel layout, and position units. Do not assume these are float stereo.
// 4. Declare DRY/WET and LENGTH parameters with SDK-supported declarations.
// 5. Map LENGTH values to beat fractions/bars and use SongPosBeats/SongBpm
//    to align the capture boundary to the musical grid.
// 6. Add the official COM class factory / DllGetClassObject registration.
// 7. Validate release behavior: when roll is disabled, playback must resume
//    from the host's correct post-roll position, not an invented offset.
