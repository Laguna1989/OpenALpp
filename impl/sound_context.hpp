#ifndef OPENALPP_SOUND_CONTEXT_HPP
#define OPENALPP_SOUND_CONTEXT_HPP

#include "alc.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace oalpp {

class SoundContext {
public:
    SoundContext();
    ~SoundContext();

private:
    ALCdevice* m_device { nullptr };
    ALCcontext* m_context { nullptr };
    static int numberOfInitializations;
};

} // namespace oalpp

#endif // OPENALPP_SOUND_CONTEXT_HPP
