# Using Analog Comparator across targets

The only project dependency is the matching `comparator-contract`. Keep its API revision aligned with this Core.

The facade provides the same guarded enable sequence for a fixed pair and a routed pair. Application logic that depends on an edge must account for the optional event facet, its reassertion behavior and the target routing needed for interrupt delivery.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
