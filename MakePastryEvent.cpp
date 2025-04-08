#include "MakePastryEvent.h"
#include "BakePastryEvent.h"
#include "State.h"
#include <iostream>
#include <memory>

MakePastryEvent::MakePastryEvent(double t) : Event(t) {}

void MakePastryEvent::execute(State& s) {
    std::cout << "[Time " << time << "] Making pastry\n";
    s.scheduleEvent(new BakePastryEvent(time + 2));
}
