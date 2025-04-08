#include "BakePastryEvent.h"
#include "SellPastryEvent.h"
#include "State.h"
#include <iostream>
#include <memory>

BakePastryEvent::BakePastryEvent(double t) : Event(t) {}

void BakePastryEvent::execute(State& s) {
    std::cout << "[Time " << time << "] Baking pastry\n";
    s.scheduleEvent(new SellPastryEvent(time + 3));
}
