#pragma once
#include <algorithm>
#include <cstddef>
#include <vector>

// Host-independent ring buffer core. The VirtualDJ adapter should feed stereo
// interleaved float samples and call BeginRoll/Process/EndRoll at host-synced
// boundaries. This class intentionally does not guess host transport behavior.
class LoopRollEngine {
public:
    void Prepare(std::size_t capacityFrames) {
        buffer_.assign(capacityFrames * 2, 0.0f);
        writeFrame_ = 0;
        capturedFrames_ = 0;
        readFrame_ = 0;
        active_ = false;
    }

    void BeginRoll(std::size_t loopFrames) {
        if (buffer_.empty() || loopFrames == 0) return;
        loopFrames_ = std::min(loopFrames, buffer_.size() / 2);
        capturedFrames_ = 0;
        readFrame_ = 0;
        active_ = true;
        capturing_ = true;
    }

    // Capture samples into the loop. Once full, playback wraps within the loop.
    // Input/output are interleaved stereo float arrays, frames = stereo frames.
    void Process(const float* input, float* output, std::size_t frames, float wet) {
        wet = std::clamp(wet, 0.0f, 1.0f);
        if (!input || !output) return;

        for (std::size_t i = 0; i < frames; ++i) {
            const std::size_t in = i * 2;
            if (!active_) {
                output[in] = input[in];
                output[in + 1] = input[in + 1];
                continue;
            }

            if (capturing_) {
                const std::size_t dst = capturedFrames_ * 2;
                buffer_[dst] = input[in];
                buffer_[dst + 1] = input[in + 1];
                ++capturedFrames_;
                output[in] = input[in];
                output[in + 1] = input[in + 1];

                if (capturedFrames_ >= loopFrames_) {
                    capturing_ = false;
                    readFrame_ = 0;
                }
            } else {
                const std::size_t src = (readFrame_ % loopFrames_) * 2;
                output[in] = input[in] * (1.0f - wet) + buffer_[src] * wet;
                output[in + 1] = input[in + 1] * (1.0f - wet) + buffer_[src + 1] * wet;
                ++readFrame_;
            }
        }
    }

    void EndRoll() { active_ = false; capturing_ = false; }
    bool IsActive() const { return active_; }

private:
    std::vector<float> buffer_;
    std::size_t writeFrame_ = 0;
    std::size_t loopFrames_ = 0;
    std::size_t capturedFrames_ = 0;
    std::size_t readFrame_ = 0;
    bool active_ = false;
    bool capturing_ = false;
};
