#include "spriteanimation.h"

namespace cepp {

SpriteAnimation::SpriteAnimation(std::vector<Frame> &frames) : mFrames(frames)
{

}

std::string SpriteAnimation::typeName() const
{
    return "SpriteAnimation";
}

bool SpriteAnimation::loop() const
{
    return mLoop;
}

void SpriteAnimation::setLoop(bool loop)
{
    mLoop = loop;
}

int SpriteAnimation::numFrames() const
{
    return mFrames.size();
}

const SpriteAnimation::Frame *SpriteAnimation::getFrame(int idx) const
{
    if(idx >= mFrames.size())
        return 0;

    return &(mFrames[idx]);
}

} // namespace cepp
