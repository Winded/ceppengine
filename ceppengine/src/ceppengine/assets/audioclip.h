#pragma once

#include "asset.h"

namespace cepp {

class AudioClip : public Asset
{
    public:
        AudioClip(void *data, int dataSize, int numChannels, int bitsPerSample, int sampleRate);
        ~AudioClip();

        virtual std::string typeName() const;

        void *data() const;
        int dataSize() const;

        int numChannels() const;
        int bitsPerSample() const;
        int sampleRate() const;

    private:
        void *mData;
        int mDataSize, mNumChannels, mBitsPerSample, mSampleRate;
};

} // namespace cepp
