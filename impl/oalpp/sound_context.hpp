#ifndef OPENALPP_SOUND_CONTEXT_HPP
#define OPENALPP_SOUND_CONTEXT_HPP

#include "alc.hpp"
#include "sound_context_interface.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace oalpp {

class SoundContext : public SoundContextInterface {
public:
    SoundContext();
    ~SoundContext() override;

private:
    ALCdevice* m_device { nullptr };
    ALCcontext* m_context { nullptr };
    static int numberOfInitializations;
};

} // namespace oalpp

#endif // OPENALPP_SOUND_CONTEXT_HPP
