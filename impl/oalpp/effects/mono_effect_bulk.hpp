#ifndef OPENALPP_EFFECTS_MONOEFFECTINTERFACE_BULK_HPP
#define OPENALPP_EFFECTS_MONOEFFECTINTERFACE_BULK_HPP

#include <vector>

namespace oalpp {
namespace effects {
class MonoEffectBulk {
public:
    virtual ~MonoEffectBulk() = default;
    virtual std::vector<float> process(std::vector<float> const& input) = 0;

    // avoid slicing via polymorphic copy or move
    MonoEffectBulk(MonoEffectBulk const& /*other*/) = delete;
    MonoEffectBulk(MonoEffectBulk&& /*other*/) = delete;
    MonoEffectBulk& operator=(const MonoEffectBulk&) = delete;
    MonoEffectBulk& operator=(MonoEffectBulk&&) = delete;

protected:
    // allow default construction for derived classes
    MonoEffectBulk() = default;
};
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_MONOEFFECTINTERFACE_BULK_HPP
