#pragma once

// Integration notes for the official VirtualDJ SDK:
// - Build against the exact vdjPlugin8.h and vdjDsp8.h supplied by the target
//   SDK version; the headers are intentionally not copied into this repository.
// - The implementation uses the SDK's stereo 16-bit buffer contract and
//   SongPosBeats/SongBpm grid fields.
// - Validate release behavior against the host: disabling the effect must let
//   the host request the normal post-roll position rather than inventing one.
