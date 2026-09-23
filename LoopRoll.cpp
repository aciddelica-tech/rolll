/*
 * LoopRoll.cpp — VirtualDJ v8 Windows x64 audio-effect starter
 *
 * IMPORTANT:
 * This is an algorithm/implementation starter, not a directly loadable DLL.
 * VirtualDJ's exact plugin ABI, exported entry points, parameter declarations,
 * and audio callback signatures must match the SDK headers for your SDK version.
 * Add this DSP class to the SDK's official audio-effect plugin template.
 *
 * Behavior:
 * - Dry/Wet mix (0..100%)
 * - Loop length in bars: 1/32, 1/16, 1/8, 1/4, 1/2, 3/4, 1, 2, 4
 * - Loop length is interpreted as musical bars, converted using BPM and
 *   time signature numerator/denominator.
 *
 * Host integration requirements:
 * 1. Feed the class the host's current BPM and time signature.
 * 2. Call process() on interleaved or planar float audio as appropriate.
 * 3. On effect activation, capture/refresh the loop buffer at the host's
 *    beat/bar boundary, and use host beat-phase/transport data for exact sync.
 * 4. Map host slider parameters to setWet() and setLengthIndex().
 */

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

class LoopRollDSP {
public:
    enum LengthIndex {
        BAR_1_32 = 0,
        BAR_1_16,
        BAR_1_8,
        BAR_1_4,
        BAR_1_2,
        BAR_3_4,
        BAR_1,
        BAR_2,
        BAR_4,
        LENGTH_COUNT
    };

    LoopRollDSP() : wet_(1.0f), lengthIndex_(BAR_1_4),
                    bpm_(120.0), beatsPerBar_(4.0), sampleRate_(44100.0),
                    writePos_(0), loopFrames_(0), active_(false), captured_(false) {}

    void setWet(float percent) {
        wet_ = std::clamp(percent / 100.0f, 0.0f, 1.0f);
    }

    void setLengthIndex(int index) {
        lengthIndex_ = std::clamp(index, 0, LENGTH_COUNT - 1);
        recalcLoopFrames();
    }

    void setTempo(double bpm, double beatsPerBar = 4.0) {
        if (bpm > 0.0) bpm_ = bpm;
        if (beatsPerBar > 0.0) beatsPerBar_ = beatsPerBar;
        recalcLoopFrames();
    }

    void prepare(double sampleRate, int channels) {
        sampleRate_ = sampleRate > 0.0 ? sampleRate : 44100.0;
        channels_ = std::max(1, channels);
        recalcLoopFrames();
        buffer_.assign(loopFrames_ * static_cast<std::size_t>(channels_), 0.0f);
        writePos_ = 0;
        active_ = false;
    }

    // Call when the host activates/deactivates the effect.
    // For sample-accurate musical sync, activate at the host's beat boundary.
    void setActive(bool active) {
        if (active && !active_) writePos_ = 0;
        active_ = active;
    }

    // Basic ring-buffer roll. `input` and `output` are interleaved float samples.
    // `frames` is the number of audio frames, not the number of samples.
    void process(const float* input, float* output, std::size_t frames) {
        if (!input || !output || channels_ < 1) return;
        const std::size_t ch = static_cast<std::size_t>(channels_);
        if (!active_ || buffer_.empty() || loopFrames_ == 0) {
            std::copy(input, input + frames * ch, output);
            return;
        }

        // First pass captures a complete loop; subsequent frames repeat it.
        for (std::size_t f = 0; f < frames; ++f) {
            const std::size_t frameIndex = writePos_ % loopFrames_;
            const std::size_t slot = frameIndex * ch;
            for (std::size_t c = 0; c < ch; ++c) {
                const float dry = input[f * ch + c];
                float wetSample = dry;
                if (captured_) {
                    wetSample = buffer_[slot + c];
                } else {
                    buffer_[slot + c] = dry;
                }
                output[f * ch + c] = dry * (1.0f - wet_) + wetSample * wet_;
            }
            ++writePos_;
            if (!captured_ && writePos_ >= loopFrames_) {
                captured_ = true;
                writePos_ = 0;
            }
        }
    }

private:
    static double barsForIndex(int index) {
        switch (index) {
            case BAR_1_32: return 1.0 / 32.0;
            case BAR_1_16: return 1.0 / 16.0;
            case BAR_1_8:  return 1.0 / 8.0;
            case BAR_1_4:  return 1.0 / 4.0;
            case BAR_1_2:  return 1.0 / 2.0;
            case BAR_3_4:  return 3.0 / 4.0;
            case BAR_1:    return 1.0;
            case BAR_2:    return 2.0;
            case BAR_4:    return 4.0;
            default:       return 1.0 / 4.0;
        }
    }

    void recalcLoopFrames() {
        // Assumes quarter-note BPM and 4/4 unless host supplies another meter.
        const double secondsPerBar = (60.0 / bpm_) * beatsPerBar_;
        const double seconds = secondsPerBar * barsForIndex(lengthIndex_);
        const double raw = seconds * sampleRate_;
        loopFrames_ = std::max<std::size_t>(1, static_cast<std::size_t>(std::llround(raw)));
        if (buffer_.size() != loopFrames_ * static_cast<std::size_t>(std::max(1, channels_))) {
            buffer_.assign(loopFrames_ * static_cast<std::size_t>(std::max(1, channels_)), 0.0f);
            writePos_ = 0;
        }
    }

    float wet_;
    int lengthIndex_;
    double bpm_, beatsPerBar_, sampleRate_;
    int channels_ = 2;
    std::size_t writePos_, loopFrames_;
    bool active_;
bool captured_;
std::vector<float> buffer_;
  
};
