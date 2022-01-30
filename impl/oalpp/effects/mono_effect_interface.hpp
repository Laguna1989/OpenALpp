#ifndef OPENALPP_EFFECTS_MONOEFFECTINTERFACE_HPP
#define OPENALPP_EFFECTS_MONOEFFECTINTERFACE_HPP

namespace oalpp {
namespace effects {
class MonoEffectInterface {
public:
    virtual ~MonoEffectInterface() = default;
    virtual float process(float input) = 0;
    virtual void reset() = 0;

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

#endif // OPENALPP_EFFECTS_MONOEFFECTINTERFACE_HPP
