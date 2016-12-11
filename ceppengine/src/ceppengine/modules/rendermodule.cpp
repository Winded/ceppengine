#include "rendermodule.h"

namespace cepp {

RenderModule::RenderModule()
{

}

std::string RenderModule::name() const
{
    return "RenderModule";
}

FT_Library RenderModule::fontLibrary() const
{
    return mFTLib;
}

void RenderModule::initialize()
{
    FT_Init_FreeType(&mFTLib);
}

} // namespace cepp
