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
    static constexpr int kLengthCount = 7;

    enum ParameterId
    {
        ID_FILTER_ROLL = 1
    };

    // Length is a bipolar control: 0 is the center/off position and either
    // direction selects the same beat length by its absolute position.
    float strengthControl_ = 1.0f;
    float lengthControl_ = 0.5f;
    float filterControl_ = 0.5f;
    int lengthIndex_ = 0;
    bool filterEnabled_ = false;

    bool active_ = false;
    int loopStart_ = 0;
    int loopSamples_ = 0;
    float filterState_[2][4] = {};
    std::vector<short> output_;

    int requestedLoopSamples() const;
    void resetFilter();
    float processFilter(float sample, int channel);
    static const char* lengthName(int index);
    static double lengthBeats(int index);
    static int controlToIndex(float value);
};
