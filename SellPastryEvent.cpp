#include "SellPastryEvent.h"
#include "State.h"
#include <iostream>
#include <random>
#include <cmath>

SellPastryEvent::SellPastryEvent(double t) : Event(t) {}

void SellPastryEvent::execute(State& s) {
    //std::cout << "[Time " << time << "] Selling pastry\n";

    // Cost function
    double a = 1.0;
    double b = std::log(10.0) / 100.0;
    double cost = a * std::exp(b * s.sell_param);

    if (s.pastriesBaked > 0) {
        s.pastriesBaked--;
        s.pastriesSold++;
        s.revenue += cost;
    } else {
        // Cost for loss of reputation (?)
        s.revenue -= cost/3;
    }

    std::random_device rd;
    std::mt19937 genX(rd());
    std::uniform_real_distribution<> distrX(std::numeric_limits<double>::epsilon(), s.sell_param);
    
    double x = distrX(genX);
    if (time + x < s.max()) {
        s.scheduleEvent(new SellPastryEvent(time + x));
    }
}
