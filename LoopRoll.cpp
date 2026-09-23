#include "LoopRoll.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

static const unsigned char kSkinPng[] = {
0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x01, 0xA4, 0x00, 0x00, 0x00, 0xBE, 0x08, 0x06, 0x00, 0x00, 0x00, 0x7A, 0x76, 0x7B, 0x7C, 0x00, 0x00, 0x02, 0xE8, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9C, 0xED, 0xD5, 0x31, 0x01, 0xC0, 0x30, 0x0C, 0xC0, 0xB0, 0xAC, 0x10, 0xC2, 0x9F, 0xEB, 0x0A, 0xA3, 0x3E, 0x24, 0x04, 0xFE, 0xFC, 0xED, 0xEE, 0x3F, 0x00, 0xF0, 0xD8, 0x79, 0x1D, 0x00, 0x00, 0x33, 0x86, 0x04, 0x40, 0x84, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x86, 0x04, 0x40, 0x82, 0x21, 0x01, 0x90, 0x60, 0x48, 0x00, 0x24, 0x18, 0x12, 0x00, 0x09, 0x17, 0x4A, 0xFB, 0x02, 0xB1, 0x35, 0x43, 0xD8, 0xB5, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

HRESULT VDJ_API LoopRollPlugin::OnLoad()
{
    active_ = false;
    loopStart_ = 0;
    loopSamples_ = 0;
    output_.clear();

    // Nine discrete choices exposed through the standard VirtualDJ effect slider.
    // The skin maps 0..100% to 1/32..4 beats, including 3/4 beat.
    lengthIndex_ = 3;
    lengthControl_ = indexToControl(lengthIndex_);
    strengthControl_ = 1.0f;
    DeclareParameterSlider(&strengthControl_, ID_STRENGTH, "Loop Roll", "Strength", strengthControl_);
    DeclareParameterSlider(&lengthControl_, ID_LENGTH, "Loop Roll", "Length", lengthControl_);
    OnParameter(ID_STRENGTH);
    OnParameter(ID_LENGTH);

    return S_OK;
}

HRESULT VDJ_API LoopRollPlugin::OnGetPluginInfo(TVdjPluginInfo8* info)
{
    if (!info)
        return E_POINTER;

    info->PluginName = "Loop Roll";
    info->Author = "Acid Delica";
    info->Description = "Synchronized Loop Roll with strength and 1/32 to 4 beat control";
    info->Version = "2.1.0";
    info->Flags = 0x00;
    info->Bitmap = NULL;
    return S_OK;
}

HRESULT VDJ_API LoopRollPlugin::OnGetUserInterface(TVdjPluginInterface8* pluginInterface)
{
    if (!pluginInterface)
        return E_POINTER;

    pluginInterface->Type = VDJINTERFACE_SKIN;
    static const char kSkinXml[] =
        "<Skin name=\"Loop Roll\" version=\"8\" width=\"390\" height=\"270\">"
        "<Copyright>Acid Delica</Copyright>"
        "<button action=\"effect active\"><pos x=\"10\" y=\"8\"/><size width=\"28\" height=\"28\"/>"
        "<off color=\"#404040\" border=\"#AAAAAA\" border_size=\"2\"/>"
        "<on color=\"green\" border=\"white\" border_size=\"2\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"ON\"/>"
        "<Tooltip>Activate Loop Roll</Tooltip></button>"
        "<textzone><pos x=\"48\" y=\"10\"/><size width=\"300\" height=\"24\"/>"
        "<text font=\"arial\" size=\"18\" weight=\"bold\" color=\"white\" action=\"get_effect_slider_text 1\"/></textzone>"
        "<slider action=\"effect slider 1\" orientation=\"round\"><pos x=\"18\" y=\"46\"/><size width=\"46\" height=\"46\"/>"
        "<off width=\"34\" height=\"34\" shape=\"circle\" color=\"#303030\" border=\"#888888\" border_size=\"2\"/>"
        "<fader color=\"#DD3333\" width=\"4\" height=\"17\" radius=\"2\" anglemin=\"-150\" anglemax=\"150\"/>"
        "<fill width=\"46\" height=\"46\" radius=\"18\" color=\"#AA2020\" backcolor=\"#202020\"/></slider>"
        "<textzone><pos x=\"72\" y=\"48\"/><size width=\"110\" height=\"18\"/>"
        "<text font=\"arial\" size=\"13\" weight=\"bold\" color=\"white\" format=\"Strength\"/></textzone>"
        "<textzone><pos x=\"72\" y=\"67\"/><size width=\"110\" height=\"18\"/>"
        "<text font=\"arial\" size=\"13\" weight=\"bold\" color=\"white\" action=\"get_effect_slider_text 1\"/></textzone>"
        "<slider action=\"effect slider 2\" orientation=\"round\"><pos x=\"18\" y=\"101\"/><size width=\"46\" height=\"46\"/>"
        "<off width=\"34\" height=\"34\" shape=\"circle\" color=\"#303030\" border=\"#888888\" border_size=\"2\"/>"
        "<fader color=\"#DD3333\" width=\"4\" height=\"17\" radius=\"2\" anglemin=\"-150\" anglemax=\"150\"/>"
        "<fill width=\"46\" height=\"46\" radius=\"18\" color=\"#AA2020\" backcolor=\"#202020\"/></slider>"
        "<textzone><pos x=\"72\" y=\"103\"/><size width=\"110\" height=\"18\"/>"
        "<text font=\"arial\" size=\"13\" weight=\"bold\" color=\"white\" format=\"Length\"/></textzone>"
        "<textzone><pos x=\"72\" y=\"122\"/><size width=\"110\" height=\"18\"/>"
        "<text font=\"arial\" size=\"13\" weight=\"bold\" color=\"white\" action=\"get_effect_slider_text 2\"/></textzone>"
        "<button action=\"effect slider 2 0%\"><size width=\"95\" height=\"32\"/><pos x=\"205\" y=\"45\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"1/32 bt\"/></button>"
        "<button action=\"effect slider 2 12.5%\"><size width=\"95\" height=\"32\"/><pos x=\"300\" y=\"45\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"1/16 bt\"/></button>"
        "<button action=\"effect slider 2 25%\"><size width=\"95\" height=\"32\"/><pos x=\"205\" y=\"80\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"1/8 bt\"/></button>"
        "<button action=\"effect slider 2 37.5%\"><size width=\"95\" height=\"32\"/><pos x=\"300\" y=\"80\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"1/4 bt\"/></button>"
        "<button action=\"effect slider 2 50%\"><size width=\"95\" height=\"32\"/><pos x=\"205\" y=\"115\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"1/2 bt\"/></button>"
        "<button action=\"effect slider 2 62.5%\"><size width=\"95\" height=\"32\"/><pos x=\"300\" y=\"115\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"3/4 bt\"/></button>"
        "<button action=\"effect slider 2 75%\"><size width=\"95\" height=\"32\"/><pos x=\"205\" y=\"150\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"1 bt\"/></button>"
        "<button action=\"effect slider 2 87.5%\"><size width=\"95\" height=\"32\"/><pos x=\"300\" y=\"150\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"2 bt\"/></button>"
        "<button action=\"effect slider 2 100%\"><size width=\"95\" height=\"32\"/><pos x=\"205\" y=\"185\"/>"
        "<off color=\"#303030\" border=\"#666666\" border_size=\"1\"/><on color=\"marine\" border=\"white\" border_size=\"1\"/>"
        "<text font=\"arial\" size=\"11\" color=\"white\" align=\"center\" format=\"4 bt\"/></button>"
        "<textzone><pos x=\"205\" y=\"225\"/><size width=\"190\" height=\"20\"/>"
        "<text font=\"arial\" size=\"11\" color=\"#AAAAAA\" align=\"left\" format=\"1/32  1/16  1/8  1/4  1/2  3/4  1  2  4 beats\"/></textzone>"
        "</Skin>";
    pluginInterface->Xml = kSkinXml;
    pluginInterface->ImageBuffer = const_cast<unsigned char*>(kSkinPng);
    pluginInterface->ImageSize = static_cast<int>(sizeof(kSkinPng));
    return S_OK;
}

HRESULT VDJ_API LoopRollPlugin::OnParameter(int id)
{
    if (id == ID_STRENGTH)
    {
        strengthControl_ = std::clamp(strengthControl_, 0.0f, 1.0f);
    }
    else if (id == ID_LENGTH)
    {
        lengthIndex_ = controlToIndex(lengthControl_);
        lengthControl_ = indexToControl(lengthIndex_);
        if (active_)
            loopSamples_ = requestedLoopSamples();
    }
    return S_OK;
}

HRESULT VDJ_API LoopRollPlugin::OnGetParameterString(int id, char* outParam, int outParamSize)
{
    if (!outParam || outParamSize <= 0)
        return E_POINTER;

    if (id == ID_STRENGTH)
    {
        std::snprintf(outParam, static_cast<size_t>(outParamSize), "%.0f%%",
                      static_cast<double>(strengthControl_ * 100.0f));
        return S_OK;
    }
    if (id == ID_LENGTH)
    {
        std::snprintf(outParam, static_cast<size_t>(outParamSize), "%s", lengthName(lengthIndex_));
        return S_OK;
    }
    return E_NOTIMPL;
}

ULONG VDJ_API LoopRollPlugin::Release()
{
    delete this;
    return 0;
}

HRESULT VDJ_API LoopRollPlugin::OnStart()
{
    if (SongBpm <= 0 || SongPos < 0)
        return E_FAIL;

    loopSamples_ = requestedLoopSamples();
    if (loopSamples_ <= 0)
        return E_FAIL;

    const double gridBeats =
        static_cast<double>(loopSamples_) / static_cast<double>(SongBpm);
    const double gridIndex = std::floor(SongPosBeats / gridBeats);
    loopStart_ = static_cast<int>(
        std::llround(gridIndex * static_cast<double>(loopSamples_)));
    active_ = true;
    return S_OK;
}

HRESULT VDJ_API LoopRollPlugin::OnStop()
{
    active_ = false;
    output_.clear();
    return S_OK;
}

int LoopRollPlugin::requestedLoopSamples() const
{
    if (SongBpm <= 0)
        return 0;

    static const double beats[kLengthCount] =
    {
        1.0 / 32.0,
        1.0 / 16.0,
        1.0 / 8.0,
        1.0 / 4.0,
        1.0 / 2.0,
        3.0 / 4.0,
        1.0,
        2.0,
        4.0
    };

    const int index = std::clamp(lengthIndex_, 0, kLengthCount - 1);
    return std::max(1, static_cast<int>(std::llround(static_cast<double>(SongBpm) * beats[index])));
}

const char* LoopRollPlugin::lengthName(int index)
{
    static const char* names[kLengthCount] =
    {
        "1/32", "1/16", "1/8", "1/4", "1/2", "3/4", "1 beat", "2 beats", "4 beats"
    };
    return names[std::clamp(index, 0, kLengthCount - 1)];
}

float LoopRollPlugin::indexToControl(int index)
{
    return static_cast<float>(std::clamp(index, 0, kLengthCount - 1)) / static_cast<float>(kLengthCount - 1);
}

int LoopRollPlugin::controlToIndex(float value)
{
    const float clamped = std::clamp(value, 0.0f, 1.0f);
    return std::clamp(static_cast<int>(std::lround(clamped * static_cast<float>(kLengthCount - 1))), 0, kLengthCount - 1);
}

short* VDJ_API LoopRollPlugin::OnGetSongBuffer(int pos, int nb)
{
    if (nb <= 0)
        return nullptr;

    output_.resize(static_cast<size_t>(nb) * 2);

    if (!active_ || loopSamples_ <= 0)
    {
        short* source = nullptr;
        if (GetSongBuffer(pos, nb, &source) != S_OK || !source)
            return nullptr;

        std::memcpy(output_.data(), source, static_cast<size_t>(nb) * 2 * sizeof(short));
        return output_.data();
    }

    int processed = 0;
    while (processed < nb)
    {
        const int absolutePosition = pos + processed;
        int relative = (absolutePosition - loopStart_) % loopSamples_;
        if (relative < 0)
            relative += loopSamples_;

        const int sourcePosition = loopStart_ + relative;
        const int remainingInLoop = loopSamples_ - relative;
        const int chunk = std::min(nb - processed, remainingInLoop);

        short* source = nullptr;
        if (GetSongBuffer(sourcePosition, chunk, &source) != S_OK || !source)
            return nullptr;

        short* dry = nullptr;
        if (GetSongBuffer(absolutePosition, chunk, &dry) != S_OK || !dry)
            return nullptr;

        const float wet = strengthControl_;
        const float dryMix = 1.0f - wet;
        for (int i = 0; i < chunk * 2; ++i)
        {
            const float mixed = static_cast<float>(dry[i]) * dryMix +
                                static_cast<float>(source[i]) * wet;
            output_[static_cast<size_t>(processed) * 2 + static_cast<size_t>(i)] =
                static_cast<short>(std::clamp(mixed, -32768.0f, 32767.0f));
        }
        processed += chunk;
    }

    return output_.data();
}
