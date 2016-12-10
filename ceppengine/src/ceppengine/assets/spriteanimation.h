#pragma once

#include "asset.h"
#include "sprite.h"

namespace cepp {

class SpriteAnimation : public Asset
{
    public:
        struct Frame
        {
                float duration;
                Sprite *sprite;
        };

        SpriteAnimation(std::vector<Frame> &frames);

        virtual std::string typeName() const;

        bool loop() const;
        void setLoop(bool loop);

        int numFrames() const;
        const Frame *getFrame(int idx) const;

    private:
        bool mLoop;
        std::vector<Frame> mFrames;
};

} // namespace cepp
