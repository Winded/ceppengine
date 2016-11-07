#pragma once

#include "module.h"

namespace cepp {

/**
 * Runtime modules handle platform-specific window handling. For example, on Windows, it creates and manages a window created using the Windows API.
 * Runtime module should be first in the engine load order, because other modules, such as RenderModule, can depend on the window context.
 */
class RuntimeModule : public Module
{
public:
    RuntimeModule();

    virtual std::string name() const;

    /**
     * Return time as seconds since engine start
     */
    float time() const;

    /**
     * Return time-scaled delta time of current frame
     */
    float deltaTime() const;
    /**
     * Return delta time of current frame, ignoring time-scale
     */
    float realDeltaTime() const;

    float timeScale() const;
    void setTimeScale(float timeScale);

    virtual std::string windowTitle() const = 0;
    virtual void setWindowTitle(std::string title) = 0;

protected:
    float mTime, mDeltaTime, mTimeScale;
};

} // namespace cepp
