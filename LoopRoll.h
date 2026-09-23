#pragma once

#include "vdjDsp8.h"
#include <vector>

class LoopRollPlugin final : public IVdjPluginBufferDsp8
{
public:
    HRESULT VDJ_API OnLoad() override;
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8* info) override;
    HRESULT VDJ_API OnGetUserInterface(TVdjPluginInterface8* pluginInterface) override;
    HRESULT VDJ_API OnParameter(int id) override;
    HRESULT VDJ_API OnGetParameterString(int id, char* outParam, int outParamSize) override;
    ULONG VDJ_API Release() override;

    HRESULT VDJ_API OnStart() override;
    HRESULT VDJ_API OnStop() override;
    short* VDJ_API OnGetSongBuffer(int pos, int nb) override;

private:
    enum ParameterId
    {
        ID_STRENGTH = 1,
        ID_LENGTH = 2
    };

    // Length is a bipolar control: 0 is the center/off position and either
    // direction selects the same beat length by its absolute position.
    float strengthControl_ = 1.0f;
    float lengthControl_ = 0.5f;
    int lengthIndex_ = 0;

    bool active_ = false;
    int loopStart_ = 0;
    int loopSamples_ = 0;
    std::vector<short> output_;

    int requestedLoopSamples() const;
    static const char* lengthName(int index);
    static float lengthBeats(int index);
    static int controlToIndex(float value);
};
