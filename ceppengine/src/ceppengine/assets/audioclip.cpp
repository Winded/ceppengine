#include "audioclip.h"
#include <algorithm>

namespace cepp {

AudioClip::AudioClip(void *data) : mData(data)
{

}

std::string AudioClip::typeName() const
{
    return "AudioClip";
}

void *AudioClip::data() const
{
    return mData;
}

} // namespace cepp
