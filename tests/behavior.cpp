#include <comparator/comparator.hpp>
#include "../examples/fake.hpp"

#include <cassert>

using namespace mhaa::comparator;
using namespace example;

class FakeEvents final : public EventControl
{
public:
    bool set_event(Event event) override { return event == Event::RisingEdge; }
    bool pending() const override { return pending_; }
    void clear_pending() override { pending_ = false; }

private:
    bool pending_ = true;
};

int main()
{
    Fake hardware;
    Comparator comparator(hardware);
    assert(!comparator.enable(InputId{}, InputId{}) && !hardware.enabled);
    assert(comparator.enable(InputId{}, static_cast<InputId>(1)));
    assert(comparator.output());
    hardware.positive_is_higher = false;
    assert(!comparator.output());
    comparator.disable();
    assert(!hardware.enabled);

    bool pending = true;
    assert(!comparator.try_event_pending(pending) && pending);
    assert(!comparator.clear_event());
    FakeEvents events;
    Comparator observable(hardware, &events);
    assert(observable.select_inputs(InputId{}, static_cast<InputId>(1)));
    observable.enable();
    assert(hardware.enabled);
    assert(!observable.set_event(Event::Change));
    assert(observable.set_event(Event::RisingEdge));
    assert(observable.try_event_pending(pending) && pending);
    assert(observable.clear_event());
    assert(observable.try_event_pending(pending) && !pending);
}
