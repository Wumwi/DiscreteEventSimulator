#include "State.h"
#include "MakePastryEvent.h"
#include <memory>

int main() {
    State s;
    s.scheduleEvent(std::make_shared<MakePastryEvent>(0));
    s.run();

    return 0;
}
