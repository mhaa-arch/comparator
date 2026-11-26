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
