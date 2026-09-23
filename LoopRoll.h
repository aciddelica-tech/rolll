#pragma once

#include "vdjDsp8.h"
#include <vector>

class LoopRollPlugin final : public IVdjPluginBufferDsp8
{
public:
    HRESULT VDJ_API OnLoad() override;
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info) override;
    ULONG VDJ_API Release() override;

    HRESULT VDJ_API OnStart() override;
    HRESULT VDJ_API OnStop() override;

    short *VDJ_API OnGetSongBuffer(int pos, int nb) override;

private:
    float wet_ = 1.0f;

    // 0 = 1/32, 1 = 1/16, 2 = 1/8,
    // 3 = 1/4, 4 = 1/2, 5 = 3/4,
    // 6 = 1, 7 = 2, 8 = 4 beats.
    int length_ = 3;

    bool active_ = false;

    int loopStart_ = 0;
    int loopSamples_ = 0;

    std::vector<short> output_;

    int requestedLoopSamples() const;
};
