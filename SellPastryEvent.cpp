#include "SellPastryEvent.h"
#include "State.h"
#include <iostream>
#include <random>

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

    std::random_device rd;
    std::mt19937 genX(rd());
    std::uniform_real_distribution<> distrX(std::numeric_limits<double>::epsilon(), s.sell_param);
    
    double x = distrX(genX);
    if (time + x < s.max()) {
        s.scheduleEvent(new SellPastryEvent(time + x));
    }
}
