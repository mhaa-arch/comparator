# Use the Analog Comparator Core

Public entry headers are [comparator/comparator.hpp](../include/comparator/comparator.hpp).

## Select, enable and observe

Construct `Comparator` from an `AnalogComparator&`. Call `enable(positive, negative)` for a checked startup. It skips enabling when selection fails. Use `select_inputs` and parameterless `enable()` if the application controls those steps separately. Wait for target-specific settling before interpreting `output()`.

Pass an `EventControl*` for the same comparator if supplied by composition. A false return from `try_event_pending(flag)` means the feature is unavailable and preserves the output. A successful query can report a false flag. Use `clear_event()` to acknowledge through that facet.

## Composition and lifetime

Application code calls the Analog Comparator Core. It borrows the matching Contract, which an Adapter implements using its Hardware Definitions. Future Devices will create or bind these objects and establish their lifetime. To use the examples today, construct the facade directly with the supplied fake. Keep each borrowed resource alive for its use by the facade and follow the Adapter's access and synchronization requirements.
