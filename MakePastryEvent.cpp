#include "MakePastryEvent.h"
#include "BakePastryEvent.h"
#include "State.h"
#include <iostream>
#include <memory>

MakePastryEvent::MakePastryEvent(double t) : Event(t) {}

void MakePastryEvent::execute(State& s) {
    //std::cout << "[Time " << time << "] Making pastry\n";

    // Cap unbaked pastries at 16
    if (s.pastriesMade < 16) {
        s.pastriesMade++;
    } else {
        // Inflict revenue penalty of 2
        s.revenue -= 2;
    }
}
