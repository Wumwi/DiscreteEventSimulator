#include "BakePastryEvent.h"
#include "SellPastryEvent.h"
#include "Simulator.h"
#include <iostream>
#include <memory>

BakePastryEvent::BakePastryEvent(double t) : Event(t) {}

void BakePastryEvent::execute(State& s) {
    std::cout << "[Time " << time << "] Baking pastry\n";
    s.scheduleEvent(std::make_shared<SellPastryEvent>(time + 3));
}
