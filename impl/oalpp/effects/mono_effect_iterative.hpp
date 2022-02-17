#ifndef OPENALPP_EFFECTS_MONOEFFECTINTERFACE_HPP
#define OPENALPP_EFFECTS_MONOEFFECTINTERFACE_HPP

namespace oalpp {
namespace effects {
class MonoEffectIterative {
public:
    virtual ~MonoEffectIterative() = default;
    virtual float process(float input) = 0;
    virtual void reset() = 0;

    // avoid slicing via polymorphic copy or move
    MonoEffectIterative(MonoEffectIterative const& /*other*/) = delete;
    MonoEffectIterative(MonoEffectIterative&& /*other*/) = delete;
    MonoEffectIterative& operator=(const MonoEffectIterative&) = delete;
    MonoEffectIterative& operator=(MonoEffectIterative&&) = delete;

protected:
    // allow default construction for derived classes
    MonoEffectIterative() = default;
};
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_MONOEFFECTINTERFACE_HPP
