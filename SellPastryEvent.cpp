#include "SellPastryEvent.h"
#include "State.h"
#include <iostream>

SellPastryEvent::SellPastryEvent(double t) : Event(t) {}

void SellPastryEvent::execute(State& s) {
    std::cout << "[Time " << time << "] Selling pastry\n";
    s.pastriesBaking--;
    s.pastriesSold++;
}
