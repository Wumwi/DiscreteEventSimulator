#include "SellPastryEvent.h"
#include "State.h"
#include <iostream>

SellPastryEvent::SellPastryEvent(double t) : Event(t) {}

void SellPastryEvent::execute(State& s) {
    //std::cout << "[Time " << time << "] Selling pastry\n";
    if (s.pastriesBaked > 0) {
        s.pastriesBaked--;
        s.pastriesSold++;
        s.revenue++;
    } else {
        // Cost for loss of reputation (?)
        s.revenue -= 1.5;
    }
}
