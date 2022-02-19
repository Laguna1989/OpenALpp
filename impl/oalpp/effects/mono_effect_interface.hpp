#ifndef OPENALPP_EFFECTS_MONOEFFECTINTERFACE_BULK_HPP
#define OPENALPP_EFFECTS_MONOEFFECTINTERFACE_BULK_HPP

#include <vector>

namespace oalpp {
namespace effects {
class MonoEffectInterface {
public:
    virtual ~MonoEffectInterface() = default;
    virtual std::vector<float> process(std::vector<float> const& input) = 0;

    // avoid slicing via polymorphic copy or move
    MonoEffectInterface(MonoEffectInterface const& /*other*/) = delete;
    MonoEffectInterface(MonoEffectInterface&& /*other*/) = delete;
    MonoEffectInterface& operator=(const MonoEffectInterface&) = delete;
    MonoEffectInterface& operator=(MonoEffectInterface&&) = delete;

protected:
    // allow default construction for derived classes
    MonoEffectInterface() = default;
};
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_MONOEFFECTINTERFACE_BULK_HPP
