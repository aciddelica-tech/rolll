#include "LoopRoll.h"

#include <algorithm>
#include <cstring>

HRESULT VDJ_API LoopRollPlugin::OnLoad()
{
    active_ = false;
    loopStart_ = 0;
    loopSamples_ = 0;
    output_.clear();

    return S_OK;
}

HRESULT VDJ_API LoopRollPlugin::OnGetPluginInfo(TVdjPluginInfo8 *info)
{
    if (!info)
        return E_POINTER;

    std::memset(info, 0, sizeof(TVdjPluginInfo8));

    std::strncpy(info->Name, "Loop Roll", sizeof(info->Name) - 1);
    std::strncpy(info->Author, "Acid Delica", sizeof(info->Author) - 1);
    std::strncpy(
        info->Description,
        "Buffer-based synchronized Loop Roll for VirtualDJ",
        sizeof(info->Description) - 1
    );
    std::strncpy(info->Version, "1.0.0", sizeof(info->Version) - 1);

    return S_OK;
}

ULONG VDJ_API LoopRollPlugin::Release()
{
    delete this;
    return 0;
}

HRESULT VDJ_API LoopRollPlugin::OnStart()
{
    if (SongBpm <= 0)
        return E_FAIL;

    loopSamples_ = requestedLoopSamples();

    if (loopSamples_ <= 0)
        return E_FAIL;

    const int currentSample =
        static_cast<int>(SongPosBeats * SongBpm);

    // Start from the previous complete loop grid position.
    loopStart_ =
        std::max(0, (currentSample / loopSamples_) * loopSamples_);

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

    // SongBpm is the number of samples between consecutive beats.
    static const int numerator[] = {
        1, 1, 1, 1, 1, 3, 1, 2, 4
    };

    static const int denominator[] = {
        32, 16, 8, 4, 2, 4, 1, 1, 1
    };

    const int index = std::clamp(length_, 0, 8);

    const double samples =
        static_cast<double>(SongBpm) *
        static_cast<double>(numerator[index]) /
        static_cast<double>(denominator[index]);

    return std::max(1, static_cast<int>(samples));
}

short *VDJ_API LoopRollPlugin::OnGetSongBuffer(int pos, int nb)
{
    if (nb <= 0)
        return nullptr;

    output_.resize(static_cast<size_t>(nb) * 2);

    if (!active_ || loopSamples_ <= 0)
    {
        short *source = nullptr;

        if (GetSongBuffer(pos, nb, &source) != S_OK || !source)
            return nullptr;

        std::memcpy(
            output_.data(),
            source,
            static_cast<size_t>(nb) * 2 * sizeof(short)
        );

        return output_.data();
    }

    int processed = 0;

    while (processed < nb)
    {
        const int absolutePosition = pos + processed;

        int relative =
            (absolutePosition - loopStart_) % loopSamples_;

        if (relative < 0)
            relative += loopSamples_;

        const int sourcePosition =
            loopStart_ + relative;

        const int remainingInLoop =
            loopSamples_ - relative;

        const int chunk =
            std::min(nb - processed, remainingInLoop);

        short *source = nullptr;

        if (GetSongBuffer(sourcePosition, chunk, &source) != S_OK ||
            !source)
        {
            return nullptr;
        }

        std::memcpy(
            output_.data() +
                static_cast<size_t>(processed) * 2,
            source,
            static_cast<size_t>(chunk) * 2 * sizeof(short)
        );

        processed += chunk;
    }

    return output_.data();
}
