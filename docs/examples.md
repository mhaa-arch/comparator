# Run the Analog Comparator Core example

The fake supplies two inputs. `Comparator` borrows it, accepts the pair and checks that the resulting output is high. The test returns failure if selection or output differs from the fake's configured behavior. A real caller must allow settling before probing the level.

## Example program

The [program](../examples/example.cpp) uses the [local fake](../examples/fake.hpp) to demonstrate injection. A concrete Adapter implementing the same Contract can be supplied to the same facade.

```cpp
#include <comparator/comparator.hpp>
#include "fake.hpp"

using namespace mhaa::comparator;
using namespace example;

int main()
{
    Fake hardware;
    Comparator comparator(hardware);
    return comparator.enable(InputId{}, static_cast<InputId>(1)) &&
                   comparator.output()
               ? 0
               : 1;
}
```

## Build and run

Build from this repository root. Set `contract_include` to the matching Contract's `include/` directory. The value below applies to the MHAA development workspace. Both programs exit with status 0 on success and print no output. On Windows execute `example.exe` and `behavior.exe`.

```sh
contract_include=../../contracts/comparator-contract/include
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" examples/example.cpp -o example
./example
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" tests/behavior.cpp -o behavior
./behavior
```

See the [behavior test](../tests/behavior.cpp) for the additional cases described above.
