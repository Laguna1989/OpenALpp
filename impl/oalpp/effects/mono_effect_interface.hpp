#ifndef OPENALPP_EFFECTS_MONOEFFECTINTERFACE_HPP
#define OPENALPP_EFFECTS_MONOEFFECTINTERFACE_HPP

namespace oalpp {
namespace effects {
class MonoEffectInterface {
public:
    virtual ~MonoEffectInterface() = default;
    virtual float process(float input) = 0;
    virtual void reset() = 0;
};
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_MONOEFFECTINTERFACE_HPP
