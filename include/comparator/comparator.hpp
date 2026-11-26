#ifndef MHAA_COMPARATOR_HPP
#define MHAA_COMPARATOR_HPP

#include <comparator/analog_comparator.hpp>
#include <comparator/event_control.hpp>
#include <comparator/types.hpp>

namespace mhaa
{
    namespace comparator
    {
        /** @brief Configures and observes one borrowed analog comparator. */
        class Comparator
        {
        public:
            explicit Comparator(AnalogComparator &comparator, EventControl *events = nullptr)
                : comparator_(comparator), events_(events) {}

            bool select_inputs(InputId positive, InputId negative)
            {
                return comparator_.select_inputs(positive, negative);
            }

            void enable() { comparator_.enable(); }

            /** @brief Enables the comparator only after accepting both inputs. */
            bool enable(InputId positive, InputId negative)
            {
                if (!select_inputs(positive, negative))
                {
                    return false;
                }
                comparator_.enable();
                return true;
            }

            void disable() { comparator_.disable(); }
            bool output() const { return comparator_.output(); }

            bool set_event(Event event) { return events_ && events_->set_event(event); }

            /** @brief Returns false when event observation is unavailable. */
            bool try_event_pending(bool &pending) const
            {
                if (!events_)
                {
                    return false;
                }
                pending = events_->pending();
                return true;
            }

            bool clear_event()
            {
                if (!events_)
                {
                    return false;
                }
                events_->clear_pending();
                return true;
            }

        private:
            AnalogComparator &comparator_;
            EventControl *events_;
        };
    }
}

#endif
