#ifndef MHAA_COMPARATOR_EXAMPLE_FAKE_HPP
#define MHAA_COMPARATOR_EXAMPLE_FAKE_HPP

#include <comparator/analog_comparator.hpp>
#include <comparator/event_control.hpp>

namespace example
{
    using namespace mhaa::comparator;

    class Fake final : public AnalogComparator
    {
    public:
        bool select_inputs(InputId positive, InputId negative) override
        {
            if (positive == negative)
            {
                return false;
            }
            selected = true;
            return true;
        }
        void enable() override { enabled = selected; }
        void disable() override { enabled = false; }
        bool output() const override { return enabled && positive_is_higher; }

        bool selected = false;
        bool enabled = false;
        bool positive_is_higher = true;
    };
}

#endif
