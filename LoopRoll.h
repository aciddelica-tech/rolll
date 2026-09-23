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

    static constexpr int kLengthCount = 8;

    // Continuous UI value, quantized to 8 Loop Roll lengths.
    float strengthControl_ = 1.0f;
    float lengthControl_ = 3.0f / 7.0f;
    int lengthIndex_ = 3; // 1/4 beat by default

    bool active_ = false;
    int loopStart_ = 0;
    int loopSamples_ = 0;
    std::vector<short> output_;

    int requestedLoopSamples() const;
    static const char* lengthName(int index);
    static float indexToControl(int index);
    static int controlToIndex(float value);
};
