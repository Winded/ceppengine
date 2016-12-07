#include "audioclip.h"
#include <algorithm>

namespace cepp {

AudioClip::AudioClip(void *data, int dataSize, int numChannels, int bitsPerSample, int sampleRate) :
    mData(data), mDataSize(dataSize), mNumChannels(numChannels), mBitsPerSample(bitsPerSample), mSampleRate(sampleRate)
{

}

AudioClip::~AudioClip()
{
    if(mData)
        delete mData;
}

std::string AudioClip::typeName() const
{
    return "AudioClip";
}

void *AudioClip::data() const
{
    return mData;
}

int AudioClip::dataSize() const
{
    return mDataSize;
}

int AudioClip::numChannels() const
{
    return mNumChannels;
}

int AudioClip::bitsPerSample() const
{
    return mBitsPerSample;
}

int AudioClip::sampleRate() const
{
    return mSampleRate;
}

} // namespace cepp
