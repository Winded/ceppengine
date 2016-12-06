#pragma once

#include "asset.h"

namespace cepp {

class AudioClip : public Asset
{
    public:
        AudioClip(void *data);

        virtual std::string typeName() const;

        void *data() const;

    private:
        void *mData;
};

} // namespace cepp
