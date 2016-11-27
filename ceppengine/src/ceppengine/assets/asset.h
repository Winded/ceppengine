#pragma once

#include "../object.h"

namespace cepp {

/**
 * Base class for assets
 */
class Asset : public Object
{
    public:
        Asset();

        virtual std::string typeName() const = 0;
};

} // namespace cepp
